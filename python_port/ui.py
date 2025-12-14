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
        dias = ["Lun", "Mar", "Mié", "Jue", "Vie", "Sáb"]
        for dia in range(6):
            values = []
            for hora in range(18):
                tag = self.logic.hda_aulas[aula_idx][dia][hora]
                values.append(tag if tag != "D" else "")
            self.horarios_tree.insert("", tk.END, values=values, text=dias[dia])


def _trim(bs: bytes) -> str:
    return bs.decode("latin1", errors="ignore").rstrip("\x00 ").strip()


def launch_ui() -> None:
    root = tk.Tk()
    FrontendApp(root)
    root.mainloop()


if __name__ == "__main__":
    launch_ui()
