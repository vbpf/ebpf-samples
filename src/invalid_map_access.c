typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

typedef struct bpf_map_def {
    uint32_t type;
    uint32_t key_size;
    uint32_t value_size;
    uint32_t max_entries;
    uint32_t map_flags;
    uint32_t inner_map_idx;
    uint32_t numa_node;
} bpf_map_def_t;
#define BPF_MAP_TYPE_ARRAY 2

typedef struct _t_prb_hist {
    uint32_t rnti;
    uint32_t prb_size;
    uint32_t cnt;
} t_prb_hist;

typedef struct _t_mcs_hist {
    uint32_t rnti;
    uint32_t mcs;
    uint32_t cnt;
} t_mcs_hist;

typedef struct _dl_config_stats {
    uint64_t timestamp;
    uint32_t cell_id;
    uint32_t msg_id;
    uint16_t l1_dlc_prb_hist_count;
    t_prb_hist l1_dlc_prb_hist[70];
    uint16_t l1_dlc_mcs_hist_count;
    t_mcs_hist l1_dlc_mcs_hist[15];
} dl_config_stats;

__attribute__((section("maps"), used))
bpf_map_def_t map =
    {.type = BPF_MAP_TYPE_ARRAY,
     .key_size = sizeof(int),
     .value_size = sizeof(dl_config_stats),
     .max_entries = 1};

static void* (*bpf_map_lookup_elem)(bpf_map_def_t* map, void* key) = (void*) 1;

int func(void* ctx)
{
  uint32_t key = 1;

  dl_config_stats *tmp;
  tmp = (dl_config_stats *)bpf_map_lookup_elem(&map, &key);
  if (!tmp)
    return 0;

  uint16_t ind = tmp->l1_dlc_prb_hist_count;
  if (ind < sizeof(tmp->l1_dlc_prb_hist) / sizeof(tmp->l1_dlc_prb_hist[0])) {
    tmp->l1_dlc_prb_hist[ind].cnt = tmp->l1_dlc_prb_hist_count;
  } else {
    tmp->l1_dlc_prb_hist[100000].cnt = 10;
  }

  return ind;
}
