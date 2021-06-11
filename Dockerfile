FROM debian:10.8-slim AS compile
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    wget && \
    wget https://github.com/Kitware/CMake/releases/download/v3.19.6/cmake-3.19.6-Linux-x86_64.sh && \
    /bin/sh cmake-3.19.6-Linux-x86_64.sh --skip-license
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    gcc \
    g++ \
    automake \
    git \
    autoconf \
    make \
    patch \
    libmariadb-dev \
    libmariadb-dev-compat \
    libtool \
    libssl-dev \
    binutils \
    zlibc \
    libc6 \
    libbz2-dev \
    libboost-all-dev
COPY . /mangos
RUN mkdir build && cd $_ && \
    cmake ../mangos \
      -DCMAKE_INSTALL_PREFIX=/opt/cmangos \
      -DDEBUG=0 \
      -DWARNINGS=0 \
      -DPOSTGRESQL=0 \
      -DPCH=1 \
      -DBUILD_GAME_SERVER=1 \
      -DBUILD_LOGIN_SERVER=1 \
      -DBUILD_EXTRACTORS=0 \
      -DBUILD_PLAYERBOT=1 \
      -DBUILD_AHBOT=0 \
      -DBUILD_METRICS=0 \
      -DBUILD_RECASTDEMOMOD=0 \
      -DBUILD_GIT_ID=0 \
      -DBUILD_DOCS=0 && \
    make -j$(nproc) && \
    make install -j$(nproc)

FROM debian:10.8-slim AS runtime
RUN apt-get update && apt-get install -y --no-install-recommends \
  libmariadb3 \
  libssl1.1
RUN useradd --system mangos
WORKDIR /opt/cmangos/bin


FROM runtime AS realmd
COPY --from=compile /opt/cmangos/bin/realmd /opt/cmangos/bin/realmd
RUN mkdir /var/log/realmd && \
    chown mangos:mangos /var/log/realmd
USER mangos
ENTRYPOINT ["./realmd"]

FROM runtime AS mangosd
COPY --from=compile /opt/cmangos/bin/mangosd /opt/cmangos/bin/mangosd
RUN mkdir /var/log/mangosd && \
    chown mangos:mangos /var/log/mangosd
USER mangos
ENTRYPOINT ["./mangosd"]
