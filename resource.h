
#ifndef FIELDS_OF_YONDER_RESOURCE_H
#define FIELDS_OF_YONDER_RESOURCE_H

#include <string>
#include <vector>
#include <map>
#include "globals.h"

using namespace std;

class Resources {
public:
	Resources();
	Resources getResources();
    void setResources(const map<string, int>& newResources);
    int getResourceQuantity(string type) const;
    void setResourceQuantity(string type, int quantity);
    void setResourceQuantity(int index, int quantity);
    void addResource(string type, int quantity);
    int expendResource(string type, int quantity);

private:
	map<string, int> resources;
};

#endif
