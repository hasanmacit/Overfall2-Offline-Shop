//arat

bool PyTuple_GetInteger(PyObject* poArgs, int pos, int* ret)

//altına ekle

bool PyTuple_GetLongLong(PyObject* poArgs, int pos, long long* ret)
{
	if (pos >= PyTuple_Size(poArgs))
		return false;

	PyObject * poItem = PyTuple_GetItem(poArgs, pos);
	
	if (!poItem)
		return false;
	
	*ret = PyLong_AsLongLong(poItem);
	return true;
}