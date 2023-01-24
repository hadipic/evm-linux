/****************************************************************************
**  Copyright (C) 2022 @武汉市凡迈科技有限公司
**  QQ Group: 399011436
**  Git: https://gitee.com/scriptiot/evm
**  Licence: 个人免费，企业授权
****************************************************************************/
#include "uv.h"

static void uv_remove_request_from_link(uv_req_t *handle,
                                           uv_req_t **head) {
  while (*head) {
    if (*head == handle) {
      *head = NULL;
      break;
    }
    if ((*head)->next == handle) {
      (*head)->next = handle->next;
      break;
    }
    head = &(*head)->next;
  }
  handle->next = NULL;
}

int uv_request_init(uv_loop_t *loop, uv_req_t *req, uv_req_type type,uv_req_cb cb) {
  req->cb = cb;
  req->type = type;
  QUEUE_INIT(&req->node);
  req->next = NULL;
  return 0;
}

int uv_request_pending(uv_req_t *req) {
    uv_loop_t *loop = uv_default_loop();
    EVM_ASSERT(!req->next);
    uv_req_t **pending_request = &loop->pending_requests;
    while (*pending_request) {
        EVM_ASSERT(*pending_request != req);
        pending_request = &(*pending_request)->next;
    }
    *pending_request = req;
    ++loop->reqeust_count;
    return 0;
}

void uv_run_request(uv_loop_t *loop) {
  uv_req_t *req;
  pthread_mutex_lock(&loop->async_lock);
  req = loop->pending_requests;
  loop->pending_requests = NULL;
  pthread_mutex_unlock(&loop->async_lock);

  uv_req_t *a;
  while (req != NULL) {
    if (req->cb) {
      req->cb(req, req->status);
    }
    a = (uv_req_t *) req->next;
    req->next = NULL;
    req = a;
  }
}
