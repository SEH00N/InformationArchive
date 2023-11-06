#include "pch.h"
#include "ResManager.h"
#include "PathManager.h"
#include "Texture.h"

Texture* ResManager::TexLoad(const std::wstring& key, const std::wstring& relativePath)
{
    Texture* tex = TexFind(key);
    if(tex != nullptr)
        return tex;

    std::wstring filePath = PathManager::GetInstance()->GetResourcePath();
    filePath += relativePath;

    tex = new Texture();
    tex->Load(filePath);
    tex->SetKey(key);
    tex->SetRelativePath(relativePath);
    texMap.insert({ key, tex });

    return tex;
}

Texture* ResManager::TexFind(const std::wstring& key)
{
    auto iter = texMap.find(key);
    if (iter != texMap.end())
        return iter->second;
    return nullptr;
}

void ResManager::Release()
{
    std::map<std::wstring, Texture*>::iterator iter;
    for (iter = texMap.begin(); iter != texMap.end(); ++iter)
        delete iter->second;
}
