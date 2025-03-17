$(BUILD_DIR)backend.a:
	$(MAKE) --directory=$(BACKEND_DIR) LIB_NAME=$@
	mv $(BACKEND_DIR)$@ $@

$(BUILD_DIR)frontend.a:
	$(MAKE) --directory=$(FRONTEND_DIR) LIB_NAME=$@
	mv $(FRONTEND_DIR)$@ $@