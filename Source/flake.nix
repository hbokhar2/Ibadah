{
	description = "Ibadah development environment";

	inputs = {
		nixpkgs.url = "github:NixOS/nixpkgs/e6f23dc08d3624daab7094b701aa3954923c6bbb";
	};

	outputs = {self, nixpkgs}:
	let
		system = "x86_64-linux";

		pkgs = import nixpkgs {
			inherit system;
		};
	in
	{
		devShells.${system}.default = pkgs.mkShell {
			packages = with pkgs; [
				gcc
				clang
				cmake
				scons
				godot
				gdb
			];

			shellHook = ''
				export DEV_SHELL_NAME="nix-ibadah"
				alias godot-dev='godot >/dev/null 2>&1 & disown'
				exec zsh -i
			'';
		};
	};
}
