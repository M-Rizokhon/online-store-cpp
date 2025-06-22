cat > README.md << EOL
# C++ Online Store

This is a C++ console application simulating an online store with Admin, Seller, and Buyer roles. Built to explore object-oriented programming and file handling, it lets users manage products, shop, and check out. It’s a learning project, not for production use.

## Features
- **Roles**: Admin (manage users/products), Seller (add/update products), Buyer (shop/checkout).
- **Functions**: Register/login, add products, manage cart, save data to text files.
- **Tech**: C++11, standard libraries (iostream, fstream, string).

## Setup
1. Clone the repo:
   \`\`\`bash
   git clone https://github.com/your-username/cpp-online-store.git
   \`\`\`
2. Navigate to the folder:
   \`\`\`bash
   cd cpp-online-store
   \`\`\`
3. Compile:
   \`\`\`bash
   g++ -std=c++11 src/*.cpp -o store
   \`\`\`
4. Run:
   \`\`\`bash
   ./store
   \`\`\`

## Usage
- **Guest**: View products (1), log in (2), register (3), exit (4).
- **Admin**: Manage products/users, view records, log out, exit.
- **Seller**: Add/update products, view your products, log out, exit.
- **Buyer**: Browse, add to cart, check out, log out, exit.
- Passwords must be 8+ characters with a number, symbol, uppercase, and lowercase (e.g., \`Pass123!\`).

## Limitations
- Saves data in plain-text files (\`users.txt\`, \`products.txt\`, \`records.txt\`).
- No support for concurrent use; files may corrupt if run multiple times.
- Fixed-size arrays limit scalability (e.g., 100 products per seller).

## Security Warning
**Important**: Passwords are stored in plain text in \`users.txt\`. This is for demo purposes only and **not secure**. Don’t use real passwords or share generated files. Use password hashing (e.g., bcrypt) for production.

## Contributing
Want to improve it? Fork the repo, create a branch, and submit a pull request. Stick to C++11 and add clear comments.

## License
MIT License (see [LICENSE](LICENSE)).

## Feedback
I built this to learn C++ and e-commerce concepts. Open an issue if you have suggestions or find bugs. Thanks for checking it out!
EOL
