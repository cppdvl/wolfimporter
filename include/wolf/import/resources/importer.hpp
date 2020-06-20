#ifndef __WOLF_RESOURCEIMPORT__
#define __WOLF_RESOURCEIMPORT__


namespace Wolf::Import::Resources {
    

    class SceneImporter;
    class Importer {
        
    public:
        static bool OpenImporter(const std::string& path);
        
    
    };

    class SceneImporter : public Importer {

    };

}

#endif