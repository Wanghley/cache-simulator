
<!-- PROJECT SHIELDS -->
<a name="readme-top"></a>
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]
[![Buy Me a Coffee](https://img.shields.io/badge/Buy%20Me%20a%20Coffee-FFDD00?style=for-the-badge&logo=buy-me-a-coffee&logoColor=black)](https://www.buymeacoffee.com/wanghley)

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/wanghley/cache-simulator">
    <img src="image.gif" alt="Logo" width="280">
  </a>

  <h3 align="center">Cache Simulator</h3>

  <p align="center">
    Simulate cache behavior, explore cache policies, and analyze performance.
    <br />
    <a href="#"><strong>Explore the code »</strong></a>
    <br />
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#about-the-project">About The Project</a></li>
    <li><a href="#built-with">Built With</a></li>
    <li><a href="#getting-started">Getting Started</a></li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

The Cache Simulator project allows you to simulate cache behavior, analyze various cache policies, and evaluate performance. Use this tool to gain insights into caching strategies and optimize memory access patterns. This is an implementation of a write-through write-no-allocate cache policy for testing and educational purposes.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built With

<img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="csharp" style="vertical-align:top; margin:4px"> <img src="https://img.shields.io/badge/Valgrind-A8A8A8?style=for-the-badge&logo=valgrind&logoColor=white" alt="csharp" style="vertical-align:top; margin:4px"> <img src="https://img.shields.io/badge/GNU-000000?style=for-the-badge&logo=gnu&logoColor=white" alt="csharp" style="vertical-align:top; margin:4px">

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started

To get started with the Cache Simulator, follow the instructions below:

### Prerequisites

* [GCC](https://gcc.gnu.org/)

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/wanghley/cache-simulator.git
   ```
2. Compile the code
   ```sh
   gcc -g -o cachesim cachesim.c
   ```
3. Run the code
   ```sh
   ./cachesim <trace file.txt> <cache size in kB> <Associativity> <Block size in B>

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE -->
## Usage

This C program serves as a single-level cache simulator, providing a means to understand and analyze the behavior of a cache and the underlying memory system. It can be utilized in various scenarios to explore cache performance. The usage instructions and scenarios are outlined below:

### How to Run

To run the cache simulator, use the following command in the terminal:

```bash
./cachesim <filename> <cache size kB> <associativity> <block size B>
```

Example:

```bash
./cachesim trace.txt 32 1 32
```

### Input Format

- `<filename>`: The name of the file containing memory access traces.
- `<cache size kB>`: Cache size in kilobytes.
- `<associativity>`: Cache associativity (number of ways).
- `<block size B>`: Block size in bytes.

### Scenarios and Features

1. **Memory Configuration:**
   - Addresses are 24 bits (3 bytes).
   - Addressable memory ranges from 0 to 2^24 - 1 (16 MB).
   - The machine is byte-addressable and big-endian.

2. **Cache Configuration:**
   - Cache size, associativity, and block size are powers of 2.
   - Cache size is limited to 2MB, block size is limited to 1024B.
   - No access is larger than the block size, and no access spans multiple blocks.

3. **Cache Operation:**
   - Cache is write-through and write-no-allocate.
   - The cache is initially empty.

4. **Cache Access:**
   - For each memory access, the simulator outputs whether it's a cache hit or miss.
   - If a miss occurs, the simulator loads the data from main memory.

5. **Supported Operations:**
   - `load`: Reads data from cache or main memory.
   - `store`: Writes data to cache or main memory.

### Use Cases

- **Cache Performance Analysis:**
  - Evaluate the impact of different cache configurations on hit/miss rates.
  - Understand how changes in cache size, associativity, and block size affect performance.

- **Memory Access Pattern Study:**
  - Analyze the behavior of the cache under different memory access patterns.
  - Identify scenarios where cache locality is high or low.

- **Cache Replacement Policy Testing:**
  - Observe the impact of cache replacement policies by analyzing cache hit/miss patterns.

- **Teaching and Learning:**
  - Serve as an educational tool for students learning about computer architecture and cache systems.

### Notes

- The program assumes a specific memory organization and cache policy, making it suitable for educational and analytical purposes.
- The debug mode (`DEBUG`) can be enabled for additional output during execution.

Feel free to explore and modify the code to suit specific learning or analysis requirements.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ROADMAP -->
## Roadmap

- [x] Implement basic cache simulation
- [x] Add support for different cache policies
- [ ] Optimize code for performance
- [ ] Explore additional features based on user feedback

See the [open issues](https://github.com/your_username/CacheSimulator/issues) for a full list of proposed features and known issues.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTRIBUTING -->
## Contributing

Contributions are welcome! If you have suggestions, improvements, or bug fixes, feel free to open an issue or submit a pull request.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

Wanghley Soares Martins - [@wanghley](https://instagram.com/wanghley) - wanghley@wanghley.com

Project Link: [https://github.com/your_username/CacheSimulator](https://github.com/your_username/CacheSimulator)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* [Choose an Open Source License](https://choosealicense.com)
* [GitHub Emoji Cheat Sheet](https://www.webpagefx.com/tools/emoji-cheat-sheet)
* [Img Shields](https://shields.io)
* [GitHub Pages](https://pages.github.com)
* [Font Awesome](https://fontawesome.com)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
[contributors-shield]: https://img.shields.io/github/contributors/wanghley/cache-simulator?style=for-the-badge
[contributors-url]: https://github.com/wanghley/cache-simulator/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/wanghley/cache-simulator.svg?style=for-the-badge
[forks-url]: https://github.com/wanghley/cache-simulator/network/members
[stars-shield]: https://img.shields.io/github/stars/wanghley/cache-simulator.svg?style=for-the-badge
[stars-url]: https://github.com/wanghley/cache-simulator/stargazers
[issues-shield]: https://img.shields.io/github/issues/wanghley/cache-simulator.svg?style=for-the-badge
[issues-url]: https://github.com/wanghley/cache-simulator/issues
[license-shield]: https://img.shields.io/github/license/wanghley/cache-simulator.svg?style=for-the-badge
[license-url]: https://github.com/wanghley/cache-simulator/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/wanghley
[product-screenshot]: images/screenshot.png
```
