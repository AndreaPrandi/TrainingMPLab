import struct

def read_bmp_and_convert_to_h_file(input_filename, output_filename):
    with open(input_filename, 'rb') as f:
        # Leggi l'intero file BMP
        bmp = f.read()
    
    # Estrai l'offset dall'intestazione BMP per trovare l'inizio dei dati dell'immagine
    offset = struct.unpack('<I', bmp[10:14])[0]
    
    # Estrai la larghezza e l'altezza dell'immagine dall'intestazione BMP
    width, height = struct.unpack('<II', bmp[18:26])
    
    # Calcola il numero di byte per riga nel BMP originale (arrotondato alla parola di 4 byte più vicina)
    row_padded = (width // 8 + 3) & (~3)
    
    # Prepara un bytearray per i dati convertiti
    converted_data = bytearray(width * height // 2)
    
    for row in range(height):
        for col in range(width):
            # Calcola l'indice nel BMP originale
            index = offset + (height - 1 - row) * row_padded + col // 8
            # Estrai il bit corrispondente e inverti i colori
            pixel = ((bmp[index] >> (7 - col % 8)) & 1) ^ 1  # Inversione dei colori
            
            # Mappa il bit in GS4_HMSB (0 o 0xF)
            grayscale = 0xF if pixel else 0
            
            # Calcola l'indice nel buffer convertito
            converted_index = (row * width + col) // 2
            
            # Imposta il pixel nel buffer convertito assicurandosi che l'ordine orizzontale rimanga invariato
            if col % 2 == 0:
                converted_data[converted_index] = grayscale << 4
            else:
                converted_data[converted_index] |= grayscale
    
    # Scrivi i dati convertiti nel file di output .h
    with open(output_filename, 'w') as h_file:
        h_file.write("const unsigned char converted_bmp[] = {")
        h_file.write(', '.join(f'0x{x:02x}' for x in converted_data))
        h_file.write("};\n")
    
    return "Conversione completata e file .h salvato con successo!"

def main():
    # Richiedi all'utente i nomi dei file di input e di output
    input_filename = "C:\\Users\\aprandi\\Desktop\\convertitore immagini\\Logo_BERTONE_256x35.bmp"
    output_filename = "C:\\Users\\aprandi\\Desktop\\convertitore immagini\\Bertone256x35.h"
    
    # Chiamata alla funzione di conversione
    result = read_bmp_and_convert_to_h_file(input_filename, output_filename)
    
    # Stampa il risultato dell'operazione
    print(result)

if __name__ == "__main__":
    main()
