#pragma once

const int MAX_UPPER_BOUND = 100000000;

std::set<int> GeneratePrimeNumbersSet(int upperBound);

std::string IntSetToString(const std::set<int>& primeSet);