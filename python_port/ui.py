from __future__ import annotations

import tkinter as tk
from tkinter import ttk, messagebox
import pathlib

from src.state import GlobalState
from src.logic import LisACaLogic


class FrontendApp(ttk.Frame):
    def __init__(self, master: tk.Tk, base_dir: str | pathlib.Path = "AsiHor") -> None:
        super().__init__(master)
        self.master = master
        self.base_dir = pathlib.Path(base_dir)
        self.state = None
        self.logic = None

        self.penalidades_list = None
        self.poblacion_list = None
        self.horarios_tree = None
        self.horario_final_tree = None
        self.aula_var = tk.StringVar()

        self._build_ui()
        self._load_data()

    def _build_ui(self) -> None:
        self.master.title("Horarios - Port Python")
        self.master.geometry("900x600")
        nb = ttk.Notebook(self)
        nb.pack(fill=tk.BOTH, expand=True)

        # Tab penalidades
        tab_pen = ttk.Frame(nb)
        nb.add(tab_pen, text="Penalidades")
        self.penalidades_list = tk.Listbox(tab_pen, font=("Courier New", 10))
        self.penalidades_list.pack(fill=tk.BOTH, expand=True, padx=6, pady=6)

        # Tab población
        tab_pop = ttk.Frame(nb)
        nb.add(tab_pop, text="Población")
        self.poblacion_list = tk.Listbox(tab_pop, font=("Courier New", 10))
        self.poblacion_list.pack(fill=tk.BOTH, expand=True, padx=6, pady=6)

        # Tab horarios
        tab_hor = ttk.Frame(nb)
        nb.add(tab_hor, text="Horarios (Aula)")
        top_bar = ttk.Frame(tab_hor)
        top_bar.pack(fill=tk.X, padx=6, pady=4)
        ttk.Label(top_bar, text="Aula:").pack(side=tk.LEFT)
        self.aula_combo = ttk.Combobox(top_bar, textvariable=self.aula_var, state="readonly", width=10)
        self.aula_combo.pack(side=tk.LEFT, padx=4)
        self.aula_combo.bind("<<ComboboxSelected>>", lambda e: self._refresh_horarios())
        self.horarios_tree = ttk.Treeview(tab_hor, columns=[f"H{i}" for i in range(18)], show="headings", height=18)
        for i in range(18):
            self.horarios_tree.heading(f"H{i}", text=str(i))
            self.horarios_tree.column(f"H{i}", width=45, anchor=tk.CENTER)
        self.horarios_tree.pack(fill=tk.BOTH, expand=True, padx=6, pady=6)

        # Tab horario final (formato tabla como el print de main.py)
        tab_final = ttk.Frame(nb)
        nb.add(tab_final, text="Horario final")
        cols = ("CURSO", "GRUPO", "DOCENTE", "DIA", "HORA", "AULA")
        self.horario_final_tree = ttk.Treeview(tab_final, columns=cols, show="headings")
        for col, width in zip(cols, (80, 80, 90, 90, 70, 90)):
            self.horario_final_tree.heading(col, text=col)
            self.horario_final_tree.column(col, width=width, anchor=tk.CENTER)
        vsb = ttk.Scrollbar(tab_final, orient="vertical", command=self.horario_final_tree.yview)
        self.horario_final_tree.configure(yscrollcommand=vsb.set)
        self.horario_final_tree.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=(6, 0), pady=6)
        vsb.pack(side=tk.RIGHT, fill=tk.Y, padx=(0, 6), pady=6)

        # Botonera
        btn_bar = ttk.Frame(self)
        btn_bar.pack(fill=tk.X, pady=6)
        ttk.Button(btn_bar, text="Recalcular penalidades", command=self._calc_penalidades).pack(side=tk.LEFT, padx=4)
        ttk.Button(btn_bar, text="Ejecutar GA (rápido)", command=self._run_ga).pack(side=tk.LEFT, padx=4)
        ttk.Button(btn_bar, text="Salir", command=self.master.destroy).pack(side=tk.RIGHT, padx=4)

        self.pack(fill=tk.BOTH, expand=True)

    def _load_data(self) -> None:
        if not self.base_dir.exists():
            messagebox.showerror("Error", f"No se encuentra la carpeta {self.base_dir}")
            return
        self.state = GlobalState.load(self.base_dir)
        self.logic = LisACaLogic(self.state)
        # Intenta cargar ocupación desde LSolHor si existe
        self.logic.load_from_lsolhor()
        # Aula combo
        aulas = [_trim(a.m_szcodaul) for a in self.logic.aulas] or ["A1"]
        self.aula_combo["values"] = aulas
        if aulas:
            self.aula_combo.current(0)
        self._calc_penalidades()
        self._refresh_horarios()
        self._refresh_horario_final()

    def _calc_penalidades(self) -> None:
        if not self.logic:
            return
        pen = self.logic.calc_penalties()
        self.penalidades_list.delete(0, tk.END)
        for line in pen["pen_ciclo"]:
            self.penalidades_list.insert(tk.END, line)
        # resumen población
        pop = self.logic.generar_poblacion()
        self.poblacion_list.delete(0, tk.END)
        for line in pop["poblacion"][:200]:
            self.poblacion_list.insert(tk.END, line)
        # refresca horarios
        self._refresh_horarios()
        self._refresh_horario_final()

    def _run_ga(self) -> None:
        if not self.logic:
            return
        res = self.logic.run_ga(generaciones=1, pob_size=8, mut_prob=0.2)
        messagebox.showinfo("GA", f"Mejor fitness: {res.get('mejor_fitness')}\nPenalidad: {res.get('total_penalidad')}")
        self._calc_penalidades()

    def _refresh_horarios(self) -> None:
        if not self.logic or not self.horarios_tree:
            return
        aula_sel = self.aula_var.get()
        aula_idx = 0
        for i, a in enumerate(self.logic.aulas):
            if _trim(a.m_szcodaul) == aula_sel:
                aula_idx = i
                break
        # Limpiar
        for item in self.horarios_tree.get_children():
            self.horarios_tree.delete(item)
        dias = ["Lun", "Mar", "Mie", "Jue", "Vie", "Sab"]
        for dia in range(6):
            values = []
            for hora in range(18):
                tag = self.logic.hda_aulas[aula_idx][dia][hora]
                values.append(tag if tag != "D" else "")
            self.horarios_tree.insert("", tk.END, values=values, text=dias[dia])

    def _refresh_horario_final(self) -> None:
        """Llena la tabla 'Horario final' con el mismo formato que imprime main.py."""
        if not self.logic or not self.horario_final_tree:
            return
        # Limpiar
        for item in self.horario_final_tree.get_children():
            self.horario_final_tree.delete(item)

        dias = ["Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"]
        rows = []
        for aula_idx, dias_aula in enumerate(self.logic.hda_aulas):
            aula_nombre = _trim(self.logic.aulas[aula_idx].m_szcodaul)
            for dia_idx, horas in enumerate(dias_aula):
                for hora_idx, etiqueta in enumerate(horas):
                    if etiqueta != "D":
                        curso = etiqueta[:3].strip()
                        docente = etiqueta[3:6].strip()
                        grupo = etiqueta[6:].strip()
                        hora = f"{hora_idx + 8:02}:00"
                        rows.append((curso, grupo, docente, dias[dia_idx], hora, aula_nombre, dia_idx, hora_idx, aula_idx))

        # Ordenar por dia, hora y aula para que quede coherente
        rows.sort(key=lambda r: (r[6], r[7], r[8]))
        for curso, grupo, docente, dia, hora, aula, _, _, _ in rows:
            self.horario_final_tree.insert("", tk.END, values=(curso, grupo, docente, dia, hora, aula))


def _trim(bs: bytes) -> str:
    return bs.decode("latin1", errors="ignore").rstrip("\x00 ").strip()


def launch_ui() -> None:
    root = tk.Tk()
    FrontendApp(root)
    root.mainloop()


if __name__ == "__main__":
    launch_ui()
