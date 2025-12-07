import os
import sys

# Agregar src al path
sys.path.append(os.path.join(os.path.dirname(__file__), 'src'))

from src.ct1_reader import load_all
from src.est_cur import SEstCur
from src.est_aul import SEstAul
from src.est_doc import SEstDoc
from src.est_cho import SEstCHo

def _trim(bs):
    """Decodifica bytes eliminando nulls y espacios."""
    if isinstance(bs, bytes):
        return bs.decode("latin1", errors="ignore").rstrip("\x00 ").strip()
    return str(bs).strip()

def probar_cursos():
    print("\n" + "="*70)
    print("PRUEBA 1: Decodificacion de Cursos (TCursos.ct1)")
    print("="*70)
    path = "AsiHor/TCursos.ct1"
    
    if not os.path.exists(path):
        print(f"ERROR: No encuentro {path}")
        return

    print(f"Leyendo {path}...")
    cursos = load_all(path, SEstCur)
    
    print(f"Se cargaron {len(cursos)} cursos.\n")
    print(f"{'CÓDIGO':<8} | {'NOMBRE':<40} | {'CICLO':<6} | {'HORAS'}")
    print("-" * 80)
    
    for i, c in enumerate(cursos[:10]):
        cod = _trim(c.m_szcodcur)
        nom = _trim(c.m_sznomcur)
        cic = _trim(c.m_szciccur)
        hor = _trim(c.m_sznumhor) if hasattr(c, 'm_sznumhor') else "N/A"
        print(f"{cod:<8} | {nom:<40} | {cic:<6} | {hor}")
    
    print(f"\n... y {len(cursos) - 10} cursos mas.")

def probar_aulas():
    print("\n" + "="*70)
    print("PRUEBA 2: Decodificacion de Aulas (TAulas.ct1)")
    print("="*70)
    path = "AsiHor/TAulas.ct1"
    
    if not os.path.exists(path):
        print(f"ERROR: No encuentro {path}")
        return

    print(f"Leyendo {path}...")
    aulas = load_all(path, SEstAul)
    
    print(f"Se cargaron {len(aulas)} aulas.\n")
    print(f"{'CODIGO':<8} | {'TIPO AULA':<10} | {'NIVEL':<12} | {'LIBRE'}")
    print("-" * 80)
    
    for i, a in enumerate(aulas[:10]):
        cod = _trim(a.m_szcodaul)
        tip = _trim(a.m_szctaasi)
        niv = _trim(a.m_sznivaul)
        lib = _trim(a.m_szlibre1)
        print(f"{cod:<8} | {tip:<10} | {niv:<12} | {lib}")
    
    print(f"\n... y {len(aulas) - 10} aulas mas.")

def probar_docentes():
    print("\n" + "="*70)
    print("PRUEBA 3: Decodificacion de Docentes (TDocent.ct1)")
    print("="*70)
    path = "AsiHor/TDocent.ct1"
    
    if not os.path.exists(path):
        print(f"ERROR: No encuentro {path}")
        return

    print(f"Leyendo {path}...")
    docentes = load_all(path, SEstDoc)
    
    print(f"Se cargaron {len(docentes)} docentes.\n")
    print(f"{'CODIGO':<8} | {'NOMBRE':<20} | {'APELLIDO':<20} | {'TIPO DISP'}")
    print("-" * 80)
    
    for i, d in enumerate(docentes[:10]):
        cod = _trim(d.m_szcoddoc)
        nom = _trim(d.m_sznomdoc)
        ape = _trim(d.m_szapdoce)
        tip = _trim(d.m_szctdisp)
        print(f"{cod:<8} | {nom:<20} | {ape:<20} | {tip}")
    
    print(f"\n... y {len(docentes) - 10} docentes mas.")

def probar_horas():
    print("\n" + "="*70)
    print("PRUEBA 4: Decodificacion de Horas por Curso (TCHoras.ct1)")
    print("="*70)
    path = "AsiHor/TCHoras.ct1"
    
    if not os.path.exists(path):
        print(f"ERROR: No encuentro {path}")
        return

    print(f"Leyendo {path}...")
    horas = load_all(path, SEstCHo)
    
    print(f"Se cargaron {len(horas)} registros de horas.\n")
    print(f"{'CODIGO CURSO':<12} | {'TIPO HORA':<12} | {'TIPO AULA':<12} | {'NUM HORAS'}")
    print("-" * 70)
    
    for i, h in enumerate(horas[:10]):
        cod = _trim(h.m_szcodcur)
        tho = _trim(h.m_szcthora)
        tau = _trim(h.m_szctaula)
        hor = _trim(h.m_sznumhor)
        print(f"{cod:<12} | {tho:<12} | {tau:<12} | {hor}")
    
    print(f"\n... y {len(horas) - 10} registros mas.")

def probar_integridad():
    print("\n" + "="*70)
    print("PRUEBA 5: Verificacion de Integridad de Datos")
    print("="*70)
    
    archivos = {
        "AsiHor/TCursos.ct1": SEstCur,
        "AsiHor/TAulas.ct1": SEstAul,
        "AsiHor/TDocent.ct1": SEstDoc,
        "AsiHor/TCHoras.ct1": SEstCHo,
    }
    
    for path, struct_class in archivos.items():
        if not os.path.exists(path):
            print(f"FALTA: {path}")
            continue
        
        try:
            records = load_all(path, struct_class)
            print(f"OK: {path:<30} - {len(records):>4} registros cargados")
        except Exception as e:
            print(f"ERROR en {path}: {str(e)}")

if __name__ == "__main__":
    try:
        probar_integridad()
        probar_cursos()
        probar_aulas()
        probar_docentes()
        probar_horas()
        print("\n" + "="*70)
        print("TODAS LAS PRUEBAS COMPLETADAS")
        print("="*70 + "\n")
    except Exception as e:
        print(f"\nERROR DURANTE LAS PRUEBAS: {str(e)}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    try:
        probar_integridad()
        probar_cursos()
        probar_aulas()
        probar_docentes()
        probar_horas()
        print("\n" + "="*70)
        print("TODAS LAS PRUEBAS COMPLETADAS")
        print("="*70 + "\n")
    except Exception as e:
        print(f"\nERROR DURANTE LAS PRUEBAS: {str(e)}")
        import traceback
        traceback.print_exc()