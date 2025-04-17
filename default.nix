{ pkgs ? import <nixpkgs> {} }:

let
  # https://github.com/NixOS/nixpkgs/blob/nixos-24.11/pkgs/by-name/bi/bitwuzla/package.nix
  bitwuzla = pkgs.callPackage <nixpkgs/pkgs/by-name/bi/bitwuzla/package.nix> {};
  
  localBitwuzla = bitwuzla.overrideAttrs (oldAttrs: {
    src = ./.;
    version = "main";
    doCheck = false;
  });
in
  localBitwuzla
