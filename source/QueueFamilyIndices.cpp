#include "QueueFamilyIndices.hpp"

bool QueueFamilyIndices::isComplete()
{
	return graphicsFamily.has_value() && presentationFamily.has_value();
}