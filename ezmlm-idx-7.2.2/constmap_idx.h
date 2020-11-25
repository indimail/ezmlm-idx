#ifndef CONSTMAP_H
#define CONSTMAP_H

typedef unsigned long constmap_hash;

struct constmap_entry {
  const char *input;
  int inputlen;
  constmap_hash hash;
  int next;
};

struct constmap_idx {
  unsigned int num;
  constmap_hash mask;
  int *first;
  struct constmap_entry *entries;
};

extern int constmap_idx_init(struct constmap_idx *cm,const char *s,int len,int splitchar);
extern void constmap_idx_free(struct constmap_idx *cm);
extern const char *constmap_idx(struct constmap_idx *cm,const char *s,int len);
extern const char *constmap_get(struct constmap_idx *cm,unsigned int idx);
extern int constmap_index(const struct constmap_idx *cm,const char *s,int len);
#endif
