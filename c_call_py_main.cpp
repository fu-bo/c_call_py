#ifndef PY_SSIZE_T_CLEAN
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#endif
// #include <boost/python.hpp>
#include <iostream>
#include <numpy/arrayobject.h>

// #include <boost/python/numpy.hpp>
// namespace p = boost::python;
// namespace np = boost::python::numpy;

int main(void) {
    // Initialize
    Py_Initialize();
    import_array();
    // np::initialize();

    // Import python functions
    PyObject * sys = PyImport_ImportModule("sys");
    PyObject * path = PyObject_GetAttrString(sys, "path");
    PyList_Append(path, PyUnicode_FromString(".."));
    
    PyObject * moduleString = PyUnicode_FromString((char*) "c_call_py_fun");
    PyObject * modul = PyImport_Import(moduleString);
    PyObject * dict = PyModule_GetDict(modul);
    PyObject * func = PyDict_GetItemString(dict, "pyfun");
    // PyObject * output = PyObject_CallObject(func, NULL);

    // Construct python function input
    npy_intp inputSize[2];
    inputSize[0] = 2;
    inputSize[1] = 3;
    double inputData[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

    PyObject* input = PyArray_SimpleNewFromData(2, inputSize, PyArray_FLOAT64, inputData);
    PyObject* pyArgs = PyTuple_New(1);
    PyTuple_SetItem(pyArgs, 0, input);
    // PyObject* pyValue = PyLong_FromLong(2); // Convert 2 to a Python integer.

    // Call python function
    PyObject * output = PyObject_CallObject(func, pyArgs);

    // Interpret python function output
    PyArrayObject * outputArray = reinterpret_cast<PyArrayObject *>(output);
    int outputNDim = PyArray_NDIM(outputArray);
    if (outputNDim != 2) {
      throw std::runtime_error(
        "expecting a 2D array but got " + std::to_string(outputNDim));
    }
    npy_intp* outputSize = PyArray_DIMS(outputArray);
    npy_intp outputRows = outputSize[0], outputCols = outputSize[1];
    void* outputPtr = PyArray_DATA(output);
    int* intOutputPtr = static_cast<int *>(outputPtr);
    std::cout << "outputRows = " << outputRows << "\n";
    std::cout << "outputCols = " << outputCols << "\n";
    for (int iRow = 0; iRow < outputRows; iRow++) {
        for (int iCol = 0; iCol < outputCols; iCol++) {
            int temp = intOutputPtr[iRow * outputCols + iCol];
            std::cout << temp << "\t";
        }
        std::cout << "\n";
    }

    // There are probably still some memory leaks, need to fix
    std::cout << "sys: " << Py_REFCNT(sys) << "\n";
    std::cout << "path: " << Py_REFCNT(path) << "\n";
    std::cout << "moduleString: " << Py_REFCNT(moduleString) << "\n";
    std::cout << "modul: " << Py_REFCNT(modul) << "\n";
    std::cout << "dict: " << Py_REFCNT(dict) << "\n";
    std::cout << "func: " << Py_REFCNT(func) << "\n";

    std::cout << "input: " << Py_REFCNT(input) << "\n";
    std::cout << "pyArgs: " << Py_REFCNT(pyArgs) << "\n";
    std::cout << "output: " << Py_REFCNT(output) << "\t" << PyArray_DATA(output) << "\n";
    std::cout << "outputArray: " << Py_REFCNT(outputArray) << "\t" << PyArray_DATA(outputArray) << "\n";
    std::cout << "\n";

    Py_XDECREF(pyArgs);
    Py_XDECREF(outputArray);
    // Py_XDECREF(func);
    Py_XDECREF(modul);
    Py_XDECREF(moduleString);
    Py_XDECREF(path);
    Py_Finalize();

    std::cout << "sys: " << Py_REFCNT(sys) << "\n";
    std::cout << "path: " << Py_REFCNT(path) << "\n";
    std::cout << "moduleString: " << Py_REFCNT(moduleString) << "\n";
    std::cout << "modul: " << Py_REFCNT(modul) << "\n";
    std::cout << "dict: " << Py_REFCNT(dict) << "\n";
    std::cout << "func: " << Py_REFCNT(func) << "\n";

    std::cout << "input: " << Py_REFCNT(input) << "\n";
    std::cout << "pyArgs: " << Py_REFCNT(pyArgs) << "\n";
    std::cout << "output: " << Py_REFCNT(output) << "\n";
    std::cout << "outputArray: " << Py_REFCNT(outputArray) << "\n";
    std::cout << "\n";

}
