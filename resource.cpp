
#include "resource.h"

using namespace std;

Resources::Resources() {
    // Initialize resources with names from globalMap and default quantity of 0
    for (const auto& pair : resourceTypes) {
        resources[pair.first] = 0;

    }
}

map<string, int> Resources::getResources() {
    return resources;
}



void Resources::setResources(const map<string, int>& newResources) {
    resources = newResources;
}

int Resources::getResourceQuantity(string type) const {
    auto it = resources.find(type);
    if (it != resources.end()) {
        return it->second;
    }
    return -1; // Return -1 if resource type is not found
}

void Resources::setResourceQuantity(string type, int quantity) {
    resources.at(type) = quantity;
}

void Resources::setResourceQuantity(int index, int quantity) {
    resources.at(resourceTypesIndexed.at(index)) = quantity;
}


void Resources::addResource(string type, int quantity) {
    auto it = resources.find(type);
    if (it != resources.end()) {
        it->second += quantity;
    }
}


int Resources::expendResource(string type, int quantity) {
    auto it = resources.find(type);
    if (it != resources.end()) {
        if (it->second - quantity < 0) {
            return -1;
        }
        it->second -= quantity;
    }
    return 0;
}

