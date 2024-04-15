#pragma once

#include "Stopwatch.h"

#include <iostream>
#include <memory>
#include <array>
#include <vector>

void timer_function(void (*funcPtr)(), int n, std::string title);

void test();

void t_unique_ptr();
void t_shared_ptr();

void t_stack_allocation();
void t_heap_allocation();

void analyze_vector();

void vector_test_normal();
void vector_test_reserve();
void vector_test_resize();