import ctypes
from pathlib import Path

_lib = ctypes.CDLL(str(Path(__file__).resolve().parent / "bin" / "blackScholes.dll"))

for _name in (
    "py_call_price",
    "py_put_price",
    "py_delta_call",
    "py_delta_put",
    "py_gamma",
    "py_vega",
    "py_theta_call",
    "py_theta_put",
    "py_rho_call",
    "py_rho_put",
):
    _fn = getattr(_lib, _name)
    _fn.argtypes = [ctypes.c_double] * 5
    _fn.restype = ctypes.c_double


def call_price(S: float, K: float, r: float, sigma: float, T: float) -> float:
    return float(_lib.py_call_price(S, K, r, sigma, T))


def put_price(S: float, K: float, r: float, sigma: float, T: float) -> float:
    return float(_lib.py_put_price(S, K, r, sigma, T))


def delta_call(S: float, K: float, r: float, sigma: float, T: float) -> float:
    return float(_lib.py_delta_call(S, K, r, sigma, T))

def delta_put(S: float, K: float, r: float, sigma: float, T: float) -> float:
    return float(_lib.py_delta_put(S, K, r, sigma, T))

def gamma(S: float, K: float, r: float, sigma: float, T: float) -> float:
    return float(_lib.py_gamma(S, K, r, sigma, T))

def vega(S: float, K: float, r: float, sigma: float, T: float) -> float:
    return float(_lib.py_vega(S, K, r, sigma, T))

def theta_call(S: float, K: float, r: float, sigma: float, T: float) -> float:
    return float(_lib.py_theta_call(S, K, r, sigma, T))

def theta_put(S: float, K: float, r: float, sigma: float, T: float) -> float:
    return float(_lib.py_theta_put(S, K, r, sigma, T))

def rho_call(S: float, K: float, r: float, sigma: float, T: float) -> float:
    return float(_lib.py_rho_call(S, K, r, sigma, T))

def rho_put(S: float, K: float, r: float, sigma: float, T: float) -> float:
    return float(_lib.py_rho_put(S, K, r, sigma, T))