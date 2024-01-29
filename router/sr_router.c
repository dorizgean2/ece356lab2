/**********************************************************************
 * file:  sr_router.c
 * date:  Mon Feb 18 12:50:42 PST 2002
 * Contact: casado@stanford.edu
 *
 * Description:
 *
 * This file contains all the functions that interact directly
 * with the routing table, as well as the main entry method
 * for routing.
 *
 **********************************************************************/

#include <stdio.h>
#include <assert.h>


#include "sr_if.h"
#include "sr_rt.h"
#include "sr_router.h"
#include "sr_protocol.h"
#include "sr_arpcache.h"
#include "sr_utils.h"

/*---------------------------------------------------------------------
 * Method: sr_init(void)
 * Scope:  Global
 *
 * Initialize the routing subsystem
 *
 *---------------------------------------------------------------------*/

void sr_init(struct sr_instance* sr)
{
    /* REQUIRES */
    assert(sr);

    /* Initialize cache and cache cleanup thread */
    sr_arpcache_init(&(sr->cache));

    pthread_attr_init(&(sr->attr));
    pthread_attr_setdetachstate(&(sr->attr), PTHREAD_CREATE_JOINABLE);
    pthread_attr_setscope(&(sr->attr), PTHREAD_SCOPE_SYSTEM);
    pthread_attr_setscope(&(sr->attr), PTHREAD_SCOPE_SYSTEM);
    pthread_t thread;

    pthread_create(&thread, &(sr->attr), sr_arpcache_timeout, sr);
    
    /* Add initialization code here! */

} /* -- sr_init -- */

/*---------------------------------------------------------------------
 * Method: sr_handlepacket(uint8_t* p,char* interface)
 * Scope:  Global
 *
 * This method is called each time the router receives a packet on the
 * interface.  The packet buffer, the packet length and the receiving
 * interface are passed in as parameters. The packet is complete with
 * ethernet headers.
 *
 * Note: Both the packet buffer and the character's memory are handled
 * by sr_vns_comm.c that means do NOT delete either.  Make a copy of the
 * packet instead if you intend to keep it around beyond the scope of
 * the method call.
 *
 *---------------------------------------------------------------------*/

void sr_handlepacket(struct sr_instance* sr,
        uint8_t * packet/* lent */,
        unsigned int len,
        char* interface/* lent */)
{
  /* REQUIRES */
  assert(sr);
  assert(packet);
  assert(interface);

  printf("*** -> Received packet of length %d \n",len);

  /* fill in code here */

  //check etherheader for if IP or ARP
  //uint16_t ethertype (utils)
  // break into ip and arp methods

  //IP 
    //check min length (if length is less than the size of the sr_protocols struct)
    //checksum validation cksum from header (ip sum field)
    //decrement the ttl by 1 then recompute the packet cksum over the modified header
      //discard if checksum does not match
    //check if ttl is less than one
      //if <= 1 -> send ICMP packet "Time Exceeded"
      // if >1, decrement ttl then cksum 
      //obtain destination id then check if its in our local interface
        //if in local interface <- check if ICMP or not
          //if ckcsum is valid, send echo request (ping)
          //else ignore the packet then send ICMP "Port Unreachable"
        //else
          //check routing table for longest prefix match 
            //if no match, ICMP "Destination net unreachable"
            //else: check the cache 
              //if not in the cache then send ARP request
                //if no response, send "Destination host unreachable"


  //ARP
    //check request or reply using ar_op
    //if request
      //send a reply 


    //if reply
      //update the cache

}/* end sr_ForwardPacket */

