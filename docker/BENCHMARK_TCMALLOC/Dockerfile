ARG CACHE_TAG=latest

FROM cicro/benchmark-harness:${CACHE_TAG} as harness
FROM cicro/benchmark-clang-base:${CACHE_TAG}

RUN apt-get update && apt-get install -y --no-install-recommends git autoconf autotools-dev automake libtool

ARG GPERFTOOLS_GIT_TAG=gperftools-2.7
RUN git clone --depth 1 --single-branch --branch "${GPERFTOOLS_GIT_TAG}" https://github.com/gperftools/gperftools
RUN cd gperftools && ./autogen.sh && ./configure && make install


# our benchmarking project
COPY --from=harness /benchmarks /benchmarks

# configure benchmark environment
RUN echo "LD_PRELOAD=/usr/local/lib/libtcmalloc.so.4.5.3" >> /benchmarks/configs/env.run

ENTRYPOINT ["/benchmarks/tools/bench.py", "/data/tcmalloc.json", "--filter-runtime=(tcmalloc-O3)"] FOREGROUND
