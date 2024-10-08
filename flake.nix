{
  description = "C++ Challenges project";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-23.11-darwin";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils }:
    utils.lib.eachDefaultSystem (system:
      let
        # pkgs = nixpkgs.legacyPackages.${system};
        pkgs = import nixpkgs {
          inherit system;
        };
        requiredDeps = with pkgs; [ ];
      in
      {
        packages = {
          default = pkgs.stdenv.mkDerivation {
            name = "cpp-challenges";
            src = ./.;
            nativeBuildInputs = with pkgs; [ cmake ];
            buildInputs = with pkgs; [ gcc ];

            buildPhase = ''
              cmake .
              make
            '';
            
            installPhase = ''
              mkdir -p $out/bin
              find . -type f -executable -print0 | xargs -0 -I {} cp {} $out/bin/
            '';
          };
        };

        devShells = {
          default = pkgs.mkShell {
            buildInputs = requiredDeps;
          };
        };
      });
}