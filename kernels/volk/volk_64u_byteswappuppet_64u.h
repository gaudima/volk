#ifndef INCLUDED_volk_64u_byteswappuppet_64u_H
#define INCLUDED_volk_64u_byteswappuppet_64u_H


#include <stdint.h>
#include <volk/volk_64u_byteswap.h>
#include <string.h>

#ifdef LV_HAVE_GENERIC
static inline void volk_64u_byteswappuppet_64u_generic(uint64_t*output, uint64_t* intsToSwap, unsigned int num_points){

    volk_64u_byteswap_generic((uint64_t*)intsToSwap, num_points);
    memcpy((void*)output, (void*)intsToSwap, num_points * sizeof(uint64_t));

}
#endif

#ifdef LV_HAVE_NEON
static inline void volk_64u_byteswappuppet_64u_neon(uint64_t*output, uint64_t* intsToSwap, unsigned int num_points){

    volk_64u_byteswap_neon((uint64_t*)intsToSwap, num_points);
    memcpy((void*)output, (void*)intsToSwap, num_points * sizeof(uint64_t));

}
#endif

#ifdef LV_HAVE_NEON64
static inline void volk_64u_byteswappuppet_64u_neon64(uint64_t*output, uint64_t* intsToSwap, unsigned int num_points){

    volk_64u_byteswap_neon64((uint64_t*)intsToSwap, num_points);
    memcpy((void*)output, (void*)intsToSwap, num_points * sizeof(uint64_t));

}
#endif


#ifdef LV_HAVE_SSE2
static inline void volk_64u_byteswappuppet_64u_u_sse2(uint64_t* output, uint64_t* intsToSwap, unsigned int num_points){

    volk_64u_byteswap_u_sse2((uint64_t*)intsToSwap, num_points);
    memcpy((void*)output, (void*)intsToSwap, num_points * sizeof(uint64_t));

}
#endif

#ifdef LV_HAVE_SSE2
static inline void volk_64u_byteswappuppet_64u_a_sse2(uint64_t* output, uint64_t* intsToSwap, unsigned int num_points){

    volk_64u_byteswap_a_sse2((uint64_t*)intsToSwap, num_points);
    memcpy((void*)output, (void*)intsToSwap, num_points * sizeof(uint64_t));

}
#endif

#ifdef LV_HAVE_SSSE3
static inline void volk_64u_byteswappuppet_64u_u_ssse3(uint64_t* output, uint64_t* intsToSwap, unsigned int num_points){

    volk_64u_byteswap_u_ssse3((uint64_t*)intsToSwap, num_points);
    memcpy((void*)output, (void*)intsToSwap, num_points * sizeof(uint64_t));

}
#endif

#ifdef LV_HAVE_SSSE3
static inline void volk_64u_byteswappuppet_64u_a_ssse3(uint64_t* output, uint64_t* intsToSwap, unsigned int num_points){

    volk_64u_byteswap_a_ssse3((uint64_t*)intsToSwap, num_points);
    memcpy((void*)output, (void*)intsToSwap, num_points * sizeof(uint64_t));

}
#endif

#ifdef LV_HAVE_AVX2
static inline void volk_64u_byteswappuppet_64u_u_avx2(uint64_t* output, uint64_t* intsToSwap, unsigned int num_points){

    volk_64u_byteswap_u_avx2((uint64_t*)intsToSwap, num_points);
    memcpy((void*)output, (void*)intsToSwap, num_points * sizeof(uint64_t));

}
#endif

#ifdef LV_HAVE_AVX2
static inline void volk_64u_byteswappuppet_64u_a_avx2(uint64_t* output, uint64_t* intsToSwap, unsigned int num_points){

    volk_64u_byteswap_a_avx2((uint64_t*)intsToSwap, num_points);
    memcpy((void*)output, (void*)intsToSwap, num_points * sizeof(uint64_t));

}
#endif

#endif
