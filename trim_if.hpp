#pragma once

#include <algorithm>
#include <concepts>
#include <cstdint>
#include <emmintrin.h>
#include <immintrin.h>

#include "find_n_of.hpp"

namespace ddaof {
/**
 * @brief Trims characters from the beginning and end of a sequence based on a target character.
 * 
 * This function removes all characters from the start of the input sequence up to the first occurrence 
 * of the specified target character and all characters from the last occurrence of the target character 
 * to the end of the sequence. The sequence is modified in place.
 * 
 * @tparam Sequence The type of the input sequence (e.g., std::string, std::vector<char>).
 * @param input An rvalue reference to the sequence that needs to be trimmed.
 * @param target_char The character that determines the trimming boundaries.
 */
template <typename Sequence>
void trim_if(Sequence& input, char target_char) {
    input.erase(input.cbegin(), ddaof::find_first_of(input.begin(), input.end(), target_char));
    input.erase(ddaof::find_last_of(input.begin(), input.end(), target_char), input.cend());
}
} // end namespace ddaof