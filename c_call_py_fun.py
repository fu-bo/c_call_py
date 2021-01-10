import numpy as np
import sys

def pyfun(py_input):
    print('py_input.shape = ', py_input.shape)
    print('py_input = ', py_input)
    # return np.arange(12).reshape(3,4)
    return np.arange(12).astype(np.int32).reshape(3,4)

if __name__ == '__main__':
    py_input = np.arange(6).reshape(2,3)
    pyfun(py_input)