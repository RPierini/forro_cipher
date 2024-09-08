CC=gcc
CFLAGS=-march=native -mtune=native -O3 -fomit-frame-pointer -fwrapv

FORRO_NEON_SRC=src/forro/arm-neon/forro.c
FORRO_REF_SRC=src/forro/ref/forro.c
FORRO_DEBUG_SRC=src/forro/ref/forro-debug.c
FORRO_ARG_SRC=src/forro/forro-args.c
FORRO_DRA_SRC=src/forro/forro-args-dra.c
FORRO_X86_SRC=src/forro/x86-simd/forro.c
XOTE_REF_SRC=src/xote/ref/xote.c
XOTE_X86_SRC=src/xote/x86-simd/xote.c

TEST_REF_SRC=test/test_ref.c
TEST_X86_SRC=test/test_x86_simd.c
TEST_NEON_SRC=test/test_neon.c

BUILD_DIR=build

.PHONY: ref x86_simd neon test_ref test_x86_simd test_neon

$(BUILD_DIR)/test_ref: ref
	@$(CC) $(CFLAGS) -I. $(BUILD_DIR)/xote_ref.o $(BUILD_DIR)/forro_ref.o $(TEST_REF_SRC) -o $@

$(BUILD_DIR)/test_x86_simd: x86_simd
	@$(CC) $(CFLAGS) -I. $(BUILD_DIR)/xote_x86_simd.o $(BUILD_DIR)/forro_x86_simd.o $(TEST_X86_SRC) -o $@

$(BUILD_DIR)/test_neon: neon
	@$(CC) $(CFLAGS) -I. $(BUILD_DIR)/forro_neon.o $(TEST_NEON_SRC) -o $@

test_ref: $(BUILD_DIR)/test_ref
ref: $(BUILD_DIR)/xote_ref.o $(BUILD_DIR)/forro_ref.o
ref-args: $(BUILD_DIR)/forro_debug.o $(BUILD_DIR)/forro-args
ref-args-dra: $(BUILD_DIR)/forro_debug.o $(BUILD_DIR)/forro-args-dra

$(BUILD_DIR)/xote_ref.o:
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $(XOTE_REF_SRC) -o $@

$(BUILD_DIR)/forro_ref.o:
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $(FORRO_REF_SRC) -o $@

$(BUILD_DIR)/forro_debug.o:
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $(FORRO_DEBUG_SRC) -o $@

$(BUILD_DIR)/forro-args:
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -I. $(BUILD_DIR)/forro_debug.o $(FORRO_ARG_SRC) -o $@

$(BUILD_DIR)/forro-args-dra:
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -I. $(BUILD_DIR)/forro_debug.o $(FORRO_DRA_SRC) -o $@

test_x86_simd: $(BUILD_DIR)/test_x86_simd
x86_simd: $(BUILD_DIR)/xote_x86_simd.o $(BUILD_DIR)/forro_x86_simd.o

$(BUILD_DIR)/xote_x86_simd.o:
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $(XOTE_X86_SRC) -o $@

$(BUILD_DIR)/forro_x86_simd.o:
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $(FORRO_X86_SRC) -o $@

test_neon: $(BUILD_DIR)/test_neon
neon: $(BUILD_DIR)/forro_neon.o

$(BUILD_DIR)/forro_neon.o:
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(CFLAGS) -c $(FORRO_NEON_SRC) -o $@

.PHONY : clean
clean:
	@rm -r $(BUILD_DIR)
