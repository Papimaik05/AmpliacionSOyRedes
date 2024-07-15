UNOOOOOOOOOOOOO

Ejemplo de configuración en
/etc/bind/named.conf:

zone "examen.es." {
type master;
file "/etc/bind/examen.es";
};
// CAMBIaR COMILLAS

named-checkconf

DOOOOOOOOOOOOOS
//METERTE EN EL FILE
Ejemplo de fichero de zona en
/etc/bind/examen.es:

//COPIAS LO DEL PROFE
A ES IPv4
AAA ES IPv6
MX es mail  y tienes un numero delante
CNAME ES CANONCIO
GNU nano 6.2                   /etc/bind/examen.es                            
$TTL 2d
$ORIGIN examen.es.
examen.es. IN SOA ns.examen.com. contact.examen.es. (
        2003080800 ; serial number
        3h ; refresh
        15M ; update retry
        3W12h ; expiry
        2h20M ; nx ttl
        )

        IN NS ns
        IN MX 10 mail  //ACORDARSE DE ESTO
ns      IN A 192.168.0.1
www     IN A 192.168.0.200
mail    IN A 192.168.0.250
servidor  IN CNAME mail


named-checkzone <zona> <fichero>
                examen.es. /etc/bind/examen.es


EN LA OTRA MAQUINA 
Fichero /etc/resolv.conf .....> nameserver <dirección IP del servidor DNS>
