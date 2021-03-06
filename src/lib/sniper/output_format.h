#pragma once

#include "allele_util.h"
#include "dqstats.h"

#include <stddef.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    int genotype;
    int joint_genotype;
    int joint_consensus_quality;
    int consensus_quality;
    int variant_allele_quality;
    int mean_mapping_quality;
    int somatic_score;
    variant_status_t variant_status;
    dqstats_t dqstats;
} sample_data_t;

typedef struct {
    const char* seq_name;
    uint32_t pos;

    /* genotype data*/
    int ref_base;
    int ref_base4;

    sample_data_t tumor;
    sample_data_t normal;
} sniper_output_t;

typedef struct {
    const char *refseq;
    const char *normal_sample_id;
    const char *tumor_sample_id;
} header_data_t;

typedef void(*output_fn)(FILE*, const sniper_output_t*);
typedef void(*output_header_fn)(FILE*, const header_data_t*);

typedef struct {
    FILE *fh;
    output_header_fn header_fn;
    output_fn output_fn;
    void *data; /* instance specific data */
} output_formatter_t;

uint32_t n_output_formatters();
const char* output_formatter_name(uint32_t idx);
output_formatter_t output_formatter_create(const char* name, FILE* fh);
void output_formatter_write(const output_formatter_t *formatter, const sniper_output_t *p);

#ifdef __cplusplus
}
#endif
