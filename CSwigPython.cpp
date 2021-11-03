// CSwigPython.cpp : Defines the entry point for the application.
//
#ifdef _DEBUG
#undef _DEBUG
#include <python.h>
#define _DEBUG
#else
#include <python.h>
#endif
#include <stdexcept>

using namespace std;

int main()
{
	Py_Initialize();

	PyObject *pSys = nullptr;
	PyObject *pSysPath = nullptr;
	PyObject *pFolderPath = nullptr;
	PyObject *pName = nullptr;
	PyObject *pModule = nullptr;
	PyObject *pDict = nullptr;
	PyObject *pFunc = nullptr;

	PyObject *pType = nullptr;
	PyObject *pValue = nullptr;
	PyObject *pTraceback = nullptr;
	PyObject *pExceptionStr = nullptr;
	const char *pExceptionMessage = nullptr;
	string strErrorMessage;
	bool isError = true;

	do {
		pSys = PyImport_ImportModule("sys");
		if (!pSys) break;

		pSysPath = PyObject_GetAttrString(pSys, "path");
		if (!pSysPath) break;

		pFolderPath = PyUnicode_FromString(".");
		if (!pFolderPath) break;

		if (PyList_Append(pSysPath, pFolderPath) != 0) break;

		pName = PyUnicode_FromString("pytest");
		if (!pName) break;

		pModule = PyImport_Import(pName);
		if (!pModule) break;

		pDict = PyModule_GetDict(pModule);
		if (!pDict) break;

		pFunc = PyDict_GetItemString(pDict, "do_stuff");
		if (!pFunc) break;
		if (!PyCallable_Check(pFunc)) break;

		if (PyObject_CallObject(pFunc, nullptr) == nullptr) break;

		isError = false;
	} while (false);

	if (isError) {
		PyErr_Fetch(&pType, &pValue, &pTraceback);

		pExceptionStr = PyObject_Str(pValue);

		// Docs: The caller is not responsible for deallocating the buffer.
		if (pExceptionStr && (pExceptionMessage = PyUnicode_AsUTF8(pExceptionStr))) {
			strErrorMessage = pExceptionMessage;
		}
		else {
			strErrorMessage = "unknown error in Python code";
		}
	}

	// Cleanup.
	if (pFunc) Py_XDECREF(pFunc);

	if (pDict) Py_XDECREF(pDict);

	if (pModule) Py_XDECREF(pModule);

	if (pName) Py_XDECREF(pName);

	if (pSys) Py_XDECREF(pSys);

	if (pSysPath) Py_XDECREF(pSysPath);

	if (pType) Py_XDECREF(pType);

	if (pValue) Py_XDECREF(pValue);

	if (pTraceback) Py_XDECREF(pTraceback);

	if (pExceptionStr) Py_XDECREF(pExceptionStr);

	Py_Finalize();

	if (isError) throw domain_error(strErrorMessage);

	return 0;
}
