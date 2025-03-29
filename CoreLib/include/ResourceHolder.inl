#include <iostream>

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParam)
{ 
    //assign memory, store in unique pointer
    std::unique_ptr<Resource> resource(new Resource());
    
    //load texture
    if (!resource->loadFromFile(filename, secondParam))
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

	// If loading successful, insert resource to map
    insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
    //return iterator to the found element
    auto found = mResourceMap.find(id);

	if (found == mResourceMap.end()) {
		std::cerr << "Error: Resource not found for ID: " << id << std::endl;
	}

    //assert fail if arrived at end
    assert(found != mResourceMap.end());

    //deref pointer, return second member
    return *found->second;
}

template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
    //return iterator to the found element
    auto found = mResourceMap.find(id);

	if (found == mResourceMap.end()) {
		std::cerr << "Error: Resource not found for ID: " << id << std::endl;
	}
    //assert fail if arrived at end
    //assert(found != mResourceMap.end());

    //deref pointer, return second member
    return *found->second;
}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource)
{
    //insert the texture to the map, returns success bool
    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));

    //check for success
    assert(inserted.second);
}
