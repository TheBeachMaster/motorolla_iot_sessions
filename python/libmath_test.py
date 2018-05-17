from linear_math import Linear
from pytest import approx
from decimal import *
dataRes = Linear()

def test_temp():
    getcontext().prec = 11
    a = 0.45 
    c = 10.9
    test_res = 22.339338914
    test_res = Decimal(test_res)
    lib_res = dataRes.lcdGen_tempreture(a, c)
    lib_res = Decimal(lib_res)
    assert lib_res == approx(test_res)

def test_humidity():
    getcontext().prec = 7
    a = 0.77
    c = 3.05
    test_res = 26.71305
    test_res = Decimal(test_res)
    lib_res = dataRes.lcdGen_humidity(a, c)
    lib_res = Decimal(lib_res)
    assert lib_res == approx(test_res)

def test_pressure():
    getcontext().prec = 8
    a = 0.6005
    c = 0.3875
    test_res = 0.72152212
    test_res = Decimal(test_res)
    lib_res = dataRes.lcdGen_pressure(a, c)
    lib_res = Decimal(lib_res)
    assert lib_res == approx(test_res)