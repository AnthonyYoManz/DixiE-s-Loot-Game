#pragma once
#include <map>
#include <string>
#include <functional>

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
	std::function<T*(std::string _file)> m_loaderFunc;
	std::function<void(T* _asset)> m_deleterFunc;
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

	void setLoaderFunc(std::function<T*(std::string _file)> _func)
	{
		m_loaderFunc = _func;
	}

	void setDeleterFunc(std::function<void(T* _asset)> _func)
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