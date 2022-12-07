const fs = require('fs');
const { exit } = require('process');

class File {

    files;
    parent;
    name;
    type;
    size;
    
    constructor() {
        this.files = [];
        this.size = 0;
    }

    get_size() {
        if(this.type == 1)
            return this.size;
        
        let sum = 0;
        for(const file of this.files) {
            sum += file.get_size();
        }
        return sum;
    }

    is_big_dir() {
        if(this.type == 0 && this.get_size() >= 100000)
            return true;
        return false;
    }

    to_array() {
        const arr = [];

        for(const file of this.files) {
            const file_arr = file.to_array();
        }

        if(this.is_big_dir()) {
            
        }

    }
    
    add_file(line) {
        const split = line.split(' ');
        const file = new File();
        if(split[0] === "dir") {
            file.type = 0;
        } else {
            file.size = parseInt(split[0]);
            this.size += file.size;
            file.type = 1;
        }
        file.name = split[1];
        file.parent = this;
        this.files.push(file); 
    }
    
    cd(file_name) {
        for(const file of this.files) {
            if(file.name === file_name)
            return file;
        }

        return this;
    }
};

let capture = false;
let current = new File();
current.type = 0;
let base = current;

function process_command(command, param) {
    capture = false;
    switch(command) {
        case "ls":
            capture = true;
            break;
        case "cd":

            if(param == "..")
                current = current.parent; 
            else
                current = current.cd(param);
            break;
    }
}

const file = fs.readFileSync('./data/d7t.txt').toString();
const lines = file.split('\n');
for(const line of lines) {
    const splits = line.split(' ');

    if(line[0] == '$')
        process_command(splits[1], splits[2]);
    else if(capture) {
        current.add_file(line);
    }
}

console.log(base.get_sum());