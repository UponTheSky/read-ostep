const { spawn } = require('child_process');

const num_pages = Array(12).fill(1).map((num, index) => num << index);
const num_trial = 300;

let tlb; 

num_pages.forEach(num_page => {
  tlb = spawn('./tlb', [`${num_page}`, `${num_trial}`]);
  tlb.stdout.on('data', (data) => {
    console.log(`num_page: ${num_page}, average: ${data}`);
  });
});
