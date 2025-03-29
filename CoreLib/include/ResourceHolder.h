#ifndef RESOURCE_HOLDER
#define RESOURCE_HOLDER

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceHolder
{
    public:
        void load(Identifier id, const std::string& filename) {
			std::unique_ptr<Resource> resource = std::make_unique<Resource>();
	
			// Check if Resource is sf::Font, use openFromFile instead of loadFromFile
			bool success;
			if constexpr (std::is_same_v<Resource, sf::Font>) {
				success = resource->openFromFile(filename);
			} else {
				success = resource->loadFromFile(filename);
			}
	
			if (!success)
				throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
	
			insertResource(id, std::move(resource));
		}
        
        template <typename Parameter>
        void                        load(Identifier id, const std::string& filename, const Parameter& secondparam);

        Resource&                   get(Identifier id);
        const Resource&             get(Identifier id) const; //const overload


    private:
        void                        insertResource(Identifier id, std::unique_ptr<Resource> resource);

    private:
        std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
        
};

#include "ResourceHolder.inl"
#endif //RESOURCE_HOLDER
