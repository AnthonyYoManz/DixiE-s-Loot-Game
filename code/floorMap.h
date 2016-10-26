#ifndef ANT_FLOOR_MAP

#include <string>
#include <vector>

class Scene;

class FloorMap{
private:
    bool initialised;
    unsigned int* objectHandles;
    unsigned int objectCount;
    std::string filename;
    const std::string objectKeyFilename;
public:
    FloorMap();
    void loadMap(std::string mapFile, Scene* scene);
    void reloadMap(Scene* scene);
    void unloadMap(Scene* scene);
};

#define ANT_FLOOR_MAP
#endif // ANT_MAP
