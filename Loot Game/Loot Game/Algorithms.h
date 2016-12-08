#pragma once

template <typename T> T clamp(const T& _var, const T& _low, const T& _high)
{
	T output = _var;
	output > _high ? _high : output;
	output < _low ? _low : output;
	return output;
}

template <typename T> T max(const T& _var1, const T& _var2)
{
	return (_var1 > _var2 ? _var1 : _var2);
}

template <typename T> T min(const T& _var1, const T& _var2)
{
	return (_var1 < _var2 ? _var1 : _var2);
}