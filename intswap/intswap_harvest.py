import os
from web3 import Web3, IPCProvider
from web3.providers.rpc import HTTPProvider
from web3.middleware import geth_poa_middleware
from eth_account import Account
from hexbytes import HexBytes

contract_addr = HexBytes(0xfabc64d2c75027ab59ba324a4c83a5d18948a781)
input_data = ["79ee54f70000000000000000000000008289c4dde54517f7961f782dc47d83db0287dcab",
              "79ee54f70000000000000000000000002ba3ad36c53d10f979e90ed42ae4b7d78360a4ec",
              "79ee54f7000000000000000000000000cfe9c6b42ecc7ee0e7129da9bdd1a06d6c1cb295"]

def claim(w3, account, data):
    signed = account.sign_transaction(dict(
        nonce = w3.eth.get_transaction_count(account.address),
        maxFeePerGas = 28033333489,
        maxPriorityFeePerGas = 28033333329,
        gas = 300000,
        to = contract_addr,
        value = 0,
        data = bytes.fromhex(data),
        chainId = 80001
    ))
    tx = w3.eth.send_raw_transaction(signed.rawTransaction).hex()
    w3.eth.wait_for_transaction_receipt(tx)
    print(tx + "success")

def main():
    w3 = Web3(Web3.HTTPProvider('https://rpc-mumbai.maticvigil.com/'))
    w3.middleware_onion.inject(geth_poa_middleware, layer = 0)

    key = private_key = os.environ.get("PRIVATE_KEY")
    account = Account.from_key(key)
    claim(w3, account, input_data[0])
    claim(w3, account, input_data[1])
    claim(w3, account, input_data[2])

if __name__ == "__main__":
    main()
