typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

struct ebpf_map {
    uint32_t type;
    uint32_t key_size;
    uint32_t value_size;
    uint32_t max_entries;
    uint32_t map_flags;
    uint32_t inner_map_idx;
    uint32_t numa_node;
};

#define BPF_MAP_TYPE_ARRAY 2
#define BPF_MAP_TYPE_ARRAY_OF_MAPS 12

static void* (*bpf_map_lookup_elem)(struct ebpf_map* map, const void* key) = (void*) 1;

__attribute__((section("maps/array_of_maps"), used))
struct ebpf_map array_of_maps =
    {.type = BPF_MAP_TYPE_ARRAY_OF_MAPS,
     .key_size = sizeof(uint32_t),
     .value_size = sizeof(uint32_t),
     .max_entries = 1,
     .inner_map_idx = 1}; // (uint32_t)&inner_map};

__attribute__((section("maps/inner_map"), used))
struct ebpf_map inner_map =
    {.type = BPF_MAP_TYPE_ARRAY,
     .key_size = sizeof(uint32_t),
     .value_size = sizeof(uint64_t),
     .max_entries = 1};


int func(void* ctx) {
    uint32_t outer_key = 0;
    void* nolocal_lru_map = bpf_map_lookup_elem(&array_of_maps, &outer_key);
    if (nolocal_lru_map) {
        uint32_t inner_key = 0;
        void* ret = bpf_map_lookup_elem(nolocal_lru_map, &inner_key);
        if (ret) {
            return 0;
        } else {
            ret = bpf_map_lookup_elem(&inner_map, &inner_key);
            return 0;
        }
    }
    return 0;
}
