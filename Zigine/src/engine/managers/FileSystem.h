#ifndef _FILESYSTEM_H
#define _FILESYSTEM_H
#include "engine/Zigine.h"

class FileSystem
{
public:
	FileSystem();

	void CreateDirectory(const std::string& name);
	void SetGameDirectory(const std::string& path);

	bool IsDirectory(const std::string& path);
	bool Exists(const std::string& file, const std::string& path);
	int GetFileSize(const std::string& file, const std::string& path);
	std::vector<std::string> GetFiles(const std::string& path);

	inline std::string GetGamePath() const { return m_GamePath; }
private:
	std::string m_GamePath;
};

DECLARE_INSTANCE_FUNCTION(FileSystem, Files)

#endif // !_FILESYSTEM_H
