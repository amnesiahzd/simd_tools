#pragma once

#include <algorithm>
#include <concepts>
#include <cstdint>
#include <emmintrin.h>
#include <immintrin.h>
#include <vector>

namespace ddaof {
template<typename InputIterator>
InputIterator find_first_of(InputIterator input_start, InputIterator input_end, char target_char) {
    __m128i target = _mm_set1_epi8(target_char);
    
    InputIterator loop_start = input_start;
    InputIterator res = input_end;
    constexpr long stride = 16;
    
    // tip: can we use for_each(std::execution::par, ...) to complet?
    for (; std::distance(loop_start, input_end) >= stride; loop_start += stride) {
        const char* loop_start_ptr = &(*loop_start);
        __m128i data = _mm_loadu_si128(reinterpret_cast<const __m128i*>(loop_start_ptr));
        __m128i mask = _mm_cmpeq_epi8(data, target);
        
        int m = _mm_movemask_epi8(mask);
        if (m != 0) {
            loop_start += __builtin_ctz(m);
            res = loop_start;
            return res;
        }
    }

     for (; loop_start < input_end; ++loop_start) {
        if (*loop_start == target_char) {
            return loop_start;
        }
    }
    return res;
}

template<typename InputIterator>
InputIterator find_last_of(InputIterator input_start, InputIterator input_end, char target_char) {
    __m128i target = _mm_set1_epi8(target_char);

    InputIterator loop_start = input_end;
    InputIterator res = input_end;
    constexpr long stride = 16;

    // tip: can we use for_each(std::execution::par, ...) to complet
    for (; std::distance(input_start, loop_start) >= stride; loop_start -= stride) {
        const char* loop_start_ptr = &(*(loop_start - stride));
        __m128i data = _mm_loadu_si128(reinterpret_cast<const __m128i*>(loop_start_ptr));
        __m128i mask = _mm_cmpeq_epi8(data, target);
        
        int m = _mm_movemask_epi8(mask);
        if (m != 0) {
            loop_start -= (stride - 1 - __builtin_clz(m) / 8);
            res = loop_start;
            return res;
        }
    }

    for (; loop_start > input_start; ) {
        --loop_start;
        if (*loop_start == target_char) {
            return loop_start;
        }
    }
    return res;
}
} // end namespace ddaof