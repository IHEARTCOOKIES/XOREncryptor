.PHONY: clean

# Builds the program
build:
	gcc XOREncryptor.cpp -std=c++17 -lstdc++ -fno-omit-frame-pointer -g3 -lboost_iostreams -lboost_filesystem -o XOREncryptor

DATA_DIR = data

# Generates random huge size files
data:
	mkdir $(DATA_DIR)
	mkdir $(DATA_DIR)/encrypted
	dd if=/dev/urandom bs=1024 count=1000 of=$(DATA_DIR)/xor_1mb conv=notrunc
	dd if=/dev/urandom bs=1024 count=2000 of=$(DATA_DIR)/xor_2mb conv=notrunc
	dd if=/dev/urandom bs=1024 count=4000 of=$(DATA_DIR)/xor_4mb conv=notrunc
	dd if=/dev/urandom bs=1024 count=8000 of=$(DATA_DIR)/xor_8mb conv=notrunc
	dd if=/dev/urandom bs=1024 count=12000 of=$(DATA_DIR)/xor_12mb conv=notrunc
	dd if=/dev/urandom bs=1024 count=16000 of=$(DATA_DIR)/xor_16mb conv=notrunc
	dd if=/dev/urandom bs=1024 count=24000 of=$(DATA_DIR)/xor_24mb conv=notrunc
	dd if=/dev/urandom bs=1024 count=32000 of=$(DATA_DIR)/xor_32mb conv=notrunc
	dd if=/dev/urandom bs=1024 count=48000 of=$(DATA_DIR)/xor_48mb conv=notrunc
	dd if=/dev/urandom bs=1024 count=64000 of=$(DATA_DIR)/xor_64mb conv=notrunc
	dd if=/dev/urandom bs=1024 count=128000 of=$(DATA_DIR)/xor_128mb conv=notrunc
	dd if=/dev/urandom bs=1024 count=256000 of=$(DATA_DIR)/xor_256mb conv=notrunc
	dd if=/dev/urandom bs=1024 count=512000 of=$(DATA_DIR)/xor_512mb conv=notrunc
	dd if=/dev/urandom bs=1024 count=1024000 of=$(DATA_DIR)/xor_1024mb conv=notrunc
	dd if=/dev/urandom bs=1024 count=2048000 of=$(DATA_DIR)/xor_2048mb conv=notrunc
	dd if=/dev/urandom bs=1024 count=4096000 of=$(DATA_DIR)/xor_4096mb conv=notrunc

# Cleans up
clean:
	rm -rf $(DATA_DIR)
	rm XOREncryptor
