const Queue = (function () {
  const q = function () {
    this.inStk = [];
    this.outStk = [];
  };

  q.prototype.push = function (item) {
    this.inStk.push(item);
  };

  q.prototype.pop = function () {
    if (this.outStk.length === 0) {
      while (this.inStk.length) {
        this.outStk.push(this.inStk.pop());
      }
    }
    return this.outStk.pop();
  };

  q.prototype.size = function () {
    return this.inStk.length + this.outStk.length;
  };

  return q;
})();

// Usage
function test() {
  const q = new Queue();

  q.push(3);
  q.push(5);
  q.push(7);

  console.log(q.pop());

  q.push(10);

  while (q.size()) {
    console.log(q.pop());
  }
}

// Output
// 3
// 5
// 7
// 10
