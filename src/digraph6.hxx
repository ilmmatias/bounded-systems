#pragma once

#include "graph.hxx"

#include <string>
#include <string_view>

std::string trimDigraph6(std::string_view record);
Graph parseDigraph6(std::string_view record);
