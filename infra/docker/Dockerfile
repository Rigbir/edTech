# Multi-stage build for C++ application
FROM ubuntu:22.04 AS builder

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libpq-dev \
    libhiredis-dev \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /build

# Copy CMakeLists.txt first for better caching
COPY CMakeLists.txt .

# Copy source files
COPY include/ ./include/
COPY src/ ./src/
COPY main.cpp .

# Build the project
RUN mkdir -p build && \
    cd build && \
    cmake -DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
          -DCMAKE_BUILD_TYPE=Release \
          .. && \
    make -j$(nproc)

# Runtime stage
FROM ubuntu:22.04

# Install runtime dependencies
# Note: hiredis is statically linked, so no runtime library needed
RUN apt-get update && apt-get install -y \
    libpq5 \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Create app user
RUN useradd -m -u 1000 appuser

# Set working directory
WORKDIR /app

# Copy binary from builder
COPY --from=builder /build/build/cpp_core .

# Change ownership
RUN chown appuser:appuser /app/cpp_core

# Switch to non-root user
USER appuser

# Expose port
EXPOSE 8000

# Run the application
CMD ["./cpp_core"]

