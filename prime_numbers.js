class BigUint8Array {
  constructor(size, fill, max) {
    this.size = size;
    this.fill = fill;
    this.max = max || 4294967295;

    this.arrays = [];

    this.init();
  }

  init() {
    const numArrays = Math.ceil(this.size / this.max);
    for (let i = 0; i < numArrays; i++) {
      const size = i < numArrays - 1 ? this.max : this.size - this.max * i;
      this.arrays.push(new Uint8Array(size).fill(this.fill));
    }
  }

  set(index, value) {
    const arraysIndex = ~~(index / this.max);
    if (typeof this.arrays[arraysIndex] === "undefined") {
      throw new Error(`No Uint8Array at index: ${arraysIndex}`);
    }

    const arrayIndex = index - arraysIndex * this.max;
    if (typeof this.arrays[arraysIndex][arrayIndex] === "undefined") {
      throw new Error(`Index "${arraysIndex}" is out of bounds`);
    }

    this.arrays[arraysIndex][arrayIndex] = value;
  }

  get(index) {
    const arraysIndex = ~~(index / this.max);
    if (typeof this.arrays[arraysIndex] !== "undefined") {
      const arrayIndex = index - arraysIndex * this.max;
      if (typeof this.arrays[arraysIndex][arrayIndex] !== "undefined") {
        return this.arrays[arraysIndex][arrayIndex];
      }
    }
    return undefined;
  }
}

if (typeof process.argv[2] === "undefined") {
  console.log(`node ${process.argv[1]} <max_number>`);
} else {
  const max = parseInt(process.argv[2], 10);
  if (!Number.isFinite(max) || max < 2)
    throw new Error("<max_number> must be an integer greater than 2");

  const startTime = performance.now();
  const primes = new BigUint8Array(max + 1, 1);
  for (let i = 2; i ** 2 <= max; i++) {
    if (primes.get(i)) {
      for (let j = i ** 2; j <= max; j += i) {
        primes.set(j, 0);
      }
    }
  }

  let ans = 0;
  for (let i = 2; i <= max; i++) {
    if (primes.get(i)) ans++;
  }

  console.log(`Compute time: ${performance.now() - startTime} milliseconds.`);
  console.log(`Found ${ans} prime numbers less than ${max}`);
}
