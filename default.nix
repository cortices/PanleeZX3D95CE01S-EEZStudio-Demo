{ pkgs ? import <nixpkgs> {} }:
let
in {
  shell = pkgs.mkShell {
    buildInputs = [
      pkgs.platformio
      pkgs.avrdude
    ];
  };
}
