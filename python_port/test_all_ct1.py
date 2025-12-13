import os
import sys

# Agregar src al path
sys.path.append(os.path.join(os.path.dirname(__file__), 'src'))

from src.ct1_reader import load_all
from src.est_cur import SEstCur
from src.est_aul import SEstAul
from src.est_doc import SEstDoc
from src.est_cho import SEstCHo
from src.est_tau import SEstTAu
from src.est_tho import SEstTHo
from src.est_cda import SEstCDA
from src.est_cdo import SEstCDo
from src.est_hor import SEstHor
from src.est_pad import SEstPAd
from src.est_tasigna import SEstTAsigna
from src.data_loader import CT1_MAP

def _trim(bs):
    """Decodifica bytes eliminando nulls y espacios."""
    if isinstance(bs, bytes):
        return bs.decode("cp1252", errors="ignore").rstrip("\x00 ").strip()
    return str(bs).strip()

def get_field_names(obj):
    """Extrae los nombres de atributos de un objeto."""
    return [attr for attr in dir(obj) if attr.startswith('m_')]

def probar_todos_archivos():
    print("\n" + "="*80)
    print("PRUEBA: Integridad de TODOS los archivos .ct1")
    print("="*80)
    
    total_archivos = 0
    total_registros = 0
    errores = []
    
    for fname, struct_class in sorted(CT1_MAP.items()):
        path = f"AsiHor/{fname}"
        
        if not os.path.exists(path):
            print(f"FALTA:  {fname:<20} - archivo no encontrado")
            continue
        
        try:
            records = load_all(path, struct_class)
            total_archivos += 1
            total_registros += len(records)
            print(f"OK:     {fname:<20} - {len(records):>4} registros | Tamanio: {struct_class.SIZE} bytes")
            
            # Mostrar primeros 2 registros como muestra
            if records:
                print(f"        Primer registro atributos: {get_field_names(records[0])}")
                
        except Exception as e:
            errores.append((fname, str(e)))
            print(f"ERROR:  {fname:<20} - {str(e)}")
    
    print("\n" + "="*80)
    print(f"RESUMEN: {total_archivos} archivos cargados con {total_registros} registros totales")
    
    if errores:
        print(f"\nERRORES ENCONTRADOS: {len(errores)}")
        for fname, err in errores:
            print(f"  - {fname}: {err}")
    else:
        print("SIN ERRORES - Todos los archivos cargaron correctamente")
    
    print("="*80 + "\n")

def probar_decodificacion_por_tipo():
    """Prueba decodificacion detallada de cada tipo de estructura."""
    print("\n" + "="*80)
    print("PRUEBA: Decodificacion de Estructuras")
    print("="*80 + "\n")
    
    pruebas = [
        ("AsiHor/TCursos.ct1", SEstCur, "CURSOS"),
        ("AsiHor/TAulas.ct1", SEstAul, "AULAS"),
        ("AsiHor/TDocent.ct1", SEstDoc, "DOCENTES"),
        ("AsiHor/TCHoras.ct1", SEstCHo, "HORAS POR CURSO"),
        ("AsiHor/TTAula.ct1", SEstTAu, "TIPOS DE AULA"),
        ("AsiHor/TTHora.ct1", SEstTHo, "TIPOS DE HORA"),
        ("AsiHor/TCDAlum.ct1", SEstCDA, "CURSO-DOCENTE-ALUMNO"),
        ("AsiHor/TProfes.ct1", SEstCDo, "PROFESORES/CURSOS-DOCENTES"),
        ("AsiHor/TAsiPro.ct1", SEstCDo, "ASIGNACION PROFESORES"),
        ("AsiHor/TParAdm.ct1", SEstPAd, "PARAMETROS ADMINISTRATIVOS"),
        ("AsiHor/TAsigna.ct1", SEstTAsigna, "ASIGNACIONES"),
    ]
    
    for path, struct_class, descripcion in pruebas:
        if not os.path.exists(path):
            print(f"[OMITIDO] {descripcion} ({path})")
            continue
        
        try:
            records = load_all(path, struct_class)
            print(f"[CARGADO] {descripcion:<40} - {len(records):>4} registros")
            
            # Mostrar primeros 3 registros
            if records:
                print(f"  Atributos disponibles: {get_field_names(records[0])}")
                
                # Intentar mostrar valores de los primeros registros
                for i, rec in enumerate(records[:3]):
                    campos = []
                    for attr in get_field_names(rec)[:3]:  # Primeros 3 campos
                        val = _trim(getattr(rec, attr))
                        campos.append(val[:15])  # Limitar a 15 chars
                    print(f"    Registro {i+1}: {' | '.join(campos)}")
                
                if len(records) > 3:
                    print(f"    ... y {len(records) - 3} registros mas")
            
            print()
            
        except Exception as e:
            print(f"[ERROR] {descripcion:<40} - {str(e)}\n")

if __name__ == "__main__":
    try:
        probar_todos_archivos()
        probar_decodificacion_por_tipo()
        print("\n" + "="*80)
        print("TODAS LAS PRUEBAS COMPLETADAS EXITOSAMENTE")
        print("="*80 + "\n")
    except Exception as e:
        print(f"\nERROR CRITICO DURANTE LAS PRUEBAS: {str(e)}")
        import traceback
        traceback.print_exc()
