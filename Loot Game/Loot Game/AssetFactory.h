#pragma once
#include <map>
#include <string>

template <typename T>
struct Asset
{
	T* m_asset;
	unsigned int m_count;
};

template <typename T>
class AssetFactory
{
private:
	std::map<std::string, Asset<T>> m_assets;
	T*(*m_loaderFunc)(std::string _file);
	void(*m_deleterFunc)(T* _asset);
public:
	AssetFactory()
	{
	}

	~AssetFactory()
	{
		for (std::pair<std::string, Asset<T>> pair : m_assets)
		{
			m_deleterFunc(pair.second.m_asset);
		}
		m_assets.clear();
	}

	void setLoaderFunc(T*(*_func)(std::string _file))
	{
		m_loaderFunc = _func;
	}

	void setDeleterFunc(void(*_func)(T* _asset))
	{
		m_deleterFunc = _func;
	}

	T* getAsset(std::string _file)
	{
		if (!m_assets.count(_file))
		{
			Asset<T> newAsset = { m_loaderFunc(_file), 0 };
			m_assets[_file] = newAsset;
		}
		m_assets[_file].m_count++;
		return m_assets[_file].m_asset;
	}

	void freeAsset(std::string _file)
	{
		if (m_assets.count(_file))
		{
			m_assets[_file].m_count--;
			if (m_assets[_file].m_count <= 0)
			{
				m_deleterFunc(m_assets[_file].m_asset);
				m_assets.erase(_file);
			}
		}
	}
};