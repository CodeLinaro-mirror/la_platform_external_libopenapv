#include "oapv_fuzzer.h"

#include <errno.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "inc/oapv.h"
#include "app/oapv_app_util.h"

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  oapvd_t did = NULL;
  oapvm_t mid = NULL;
  oapvd_cdesc_t cdesc;
  oapv_bitb_t bitb;
  oapv_frms_t ofrms;
  oapv_au_info_t aui;
  oapvd_stat_t stat;
  int i = 0;

  int ret = 0;

  memset(&cdesc, 0, sizeof(cdesc));
  memset(&ofrms, 0, sizeof(ofrms));
  memset(&aui, 0, sizeof(oapv_au_info_t));

  did = oapvd_create(&cdesc, &ret);
  if (did == NULL) {
    return 0;
  }

  mid = oapvm_create(&ret);
  if (OAPV_FAILED(ret)) {
    ret = -1;
    goto ERR;
  }

  if (OAPV_FAILED(oapvd_info((void *)data, size, &aui))) {
    ret = -1;
    goto ERR;
  }

  /* create decoding frame buffers */
  ofrms.num_frms = aui.num_frms;
  for (i = 0; i < ofrms.num_frms; i++) {
    oapv_frm_t *frm = &ofrms.frm[i];
    oapv_frm_info_t *finfo = &aui.frm_info[i];

    if (frm->imgb != NULL &&
        (frm->imgb->w[0] != finfo->w || frm->imgb->h[0] != finfo->h)) {
      frm->imgb->release(frm->imgb);
      frm->imgb = NULL;
    }

    if (frm->imgb == NULL) {
      frm->imgb = imgb_create(finfo->w, finfo->h, finfo->cs);
      if (frm->imgb == NULL) {
        ret = -1;
        goto ERR;
      }
    }
  }

  /* main decoding block */
  bitb.addr = (void *)data;
  bitb.ssize = size;

  ret = oapvd_decode(did, &bitb, &ofrms, mid, &stat);

  if (OAPV_FAILED(ret)) {
    ret = -1;
    goto ERR;
  }

ERR:
  if (did) oapvd_delete(did);

  if (mid) oapvm_delete(mid);

  for (int i = 0; i < ofrms.num_frms; i++) {
    if (ofrms.frm[i].imgb != NULL) {
      ofrms.frm[i].imgb->release(ofrms.frm[i].imgb);
    }
  }
  return ret;
}