main.a: frr/babeld/message.o main.o
	$(AR) $(ARFLAGS) $@ main.o frr/babeld/*.o

frr/babeld/message.o:
	apt-get install -y libpcre2-dev libtool libjson-c-dev libelf-dev libreadline-dev libcap-dev libprotobuf-c-dev \
		protobuf-c-compiler pkg-config bison flex
	cmake -D CMAKE_INSTALL_PREFIX:PATH=/usr -S libyang -B libyang/build
	cd libyang/build && $(MAKE) -j$(NPROC) && $(MAKE) install
	cd frr && ./bootstrap.sh && ./configure && $(MAKE) -j$(NPROC)
