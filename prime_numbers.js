// solves limitations with array size in JS
const bigArray = (size, fill, limit) => {
  const l = size > limit ? -~(size / limit) : 1;
  const api = {};
  // just use a native Uint8Array if we're within the limit
  if (l === 1) {
    const array = new Uint8Array(size).fill(fill);
    api.get = (index) => array[index];
    api.set = (index, value) => (array[index] = value);
  } else {
    const arrays = Array(l);
    for (let i = 0; i < l; i++) {
      const k = i < l - 1 ? limit : size - limit * i;
      arrays[i] = new Uint8Array(k).fill(fill);
    }
    api.get = (index) => {
      const arraysIndex = ~~(index / limit);
      const arrayIndex = index - arraysIndex * limit;
      return arrays[arraysIndex][arrayIndex];
    };
    api.set = (index, value) => {
      const arraysIndex = ~~(index / limit);
      const arrayIndex = index - arraysIndex * limit;
      arrays[arraysIndex][arrayIndex] = value;
    };
  }
  return api;
};

// validate inputs
const max = parseInt(process.argv[2], 10);
if (!Number.isFinite(max) || max < 2) {
  throw new Error("<max_number> must be an integer greater than 2");
}

// fill sieve
const startTime = performance.now();
const primes = bigArray(max + 2, 1, 4294967295);
for (let i = 2; i ** 2 < max; i++) {
  if (primes.get(i)) {
    // mark non-primes
    for (let j = i ** 2; j < max; j += i) primes.set(j, 0);
  }
}

// count unmarked as primes
let ans = 0;
for (let i = 0; i < max; i++) if (primes.get(i)) ans++;

console.log(`Compute time: ${performance.now() - startTime} milliseconds.`);
console.log(`Found ${ans} prime numbers less than ${max}`);
