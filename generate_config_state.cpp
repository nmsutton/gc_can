/* configure the network */
/* neuron groups */
int EC_LI_II_Multipolar_Pyramidal=sim.createGroup("EC_LI_II_Multipolar_Pyramidal", 
                            p.EC_LI_II_Multipolar_Pyramidal_Count, EXCITATORY_NEURON, ANY, GPU_CORES);  
int MEC_LII_Stellate=sim.createGroup("MEC_LII_Stellate", 
                            p.MEC_LII_Stellate_Count, EXCITATORY_NEURON, ANY, GPU_CORES);
int EC_LII_Axo_Axonic=sim.createGroup("EC_LII_Axo_Axonic", 
                            p.EC_LII_Axo_Axonic_Count, INHIBITORY_NEURON, ANY, GPU_CORES);
int MEC_LII_Basket=sim.createGroup("MEC_LII_Basket", 
                            p.MEC_LII_Basket_Count, INHIBITORY_NEURON, ANY, GPU_CORES);
int EC_LII_Basket_Multipolar=sim.createGroup("EC_LII_Basket_Multipolar", 
                            p.EC_LII_Basket_Multipolar_Count, INHIBITORY_NEURON, ANY, GPU_CORES);
int CA1_Pyramidal=sim.createGroup("CA1_Pyramidal", 
                            p.CA1_Pyramidal_Count, EXCITATORY_NEURON, ANY, GPU_CORES);
int MEC_LII_Basket_Speed=sim.createGroup("MEC_LII_Basket_Speed", 
                            p.MEC_LII_Basket_Speed_Count, INHIBITORY_NEURON, ANY, GPU_CORES);
int MEC_LII_Stellate_Speed=sim.createGroup("MEC_LII_Stellate_Speed", 
                            p.MEC_LII_Stellate_Speed_Count, EXCITATORY_NEURON, ANY, GPU_CORES);
// assign group numbers for later access
p.EC_LI_II_Multipolar_Pyramidal_Group = EC_LI_II_Multipolar_Pyramidal; // 0
p.MEC_LII_Stellate_Group = MEC_LII_Stellate; // 1
p.EC_LII_Axo_Axonic_Group = EC_LII_Axo_Axonic; // 2
p.MEC_LII_Basket_Group = MEC_LII_Basket; // 3
p.EC_LII_Basket_Multipolar_Group = EC_LII_Basket_Multipolar; // 4
p.CA1_Pyramidal_Group = CA1_Pyramidal; // 5
p.MEC_LII_Basket_Speed_Group = MEC_LII_Basket_Speed; // 6
p.MEC_LII_Stellate_Speed_Group = MEC_LII_Stellate_Speed; // 7

/* neuron type parameters */
sim.setNeuronParameters(EC_LI_II_Multipolar_Pyramidal, 204.0f, 0.0f, 0.37f, 0.0f, -70.53f, 0.0f, -39.99f, 
                                0.0f, 0.001f, 0.0f, 0.01f, 0.0f, 3.96f, 0.0f, -54.95f, 0.0f, 
                                7.0f, 0.0f, 1); // C,k,vr,vt,a,b,vpeak,c,d
                                // Ensemble file:  k,a,b,d,C,vr,vt,c,vpeak. 
                                // 1->2, 2->5, 3->6, 4->9, 5->1, 6->3, 7->4, 8->8, 9->7
sim.setNeuronParameters(MEC_LII_Stellate, 118.000000f, 0.0f, 0.62f, 0.0f, -58.53f, 0.0f, 
                                -43.52f, 0.0f, 0.003f, 0.0f, 11.690000f, 0.0f, 11.48f, 0.0f, 
                                -49.52f, 0.0f, 50.0f, 0.0f, 1);
sim.setNeuronParameters(EC_LII_Axo_Axonic, 20.0f, 0.0f,  1.0f, 0.0f, -55.0f, 0.0f, 
                                -40.0f, 0.0f, 0.15f, 0.0f, 8.0f, 0.0f, 25.0f, 0.0f, 
                                -55.0f, 0.0f, 200.0f, 0.0f, 1); 
sim.setNeuronParameters(MEC_LII_Basket, 20.0f, 0.0f,  1.0f, 0.0f, -55.0f, 0.0f, 
                                -40.0f, 0.0f, 0.15f, 0.0f, 8.0f, 0.0f, 25.0f, 0.0f, 
                                -55.0f, 0.0f, 200.0f, 0.0f, 1); 
sim.setNeuronParameters(EC_LII_Basket_Multipolar, 20.0f, 0.0f,  1.0f, 0.0f, -55.0f, 0.0f, 
                                -40.0f, 0.0f, 0.15f, 0.0f, 8.0f, 0.0f, 25.0f, 0.0f, 
                                -55.0f, 0.0f, 200.0f, 0.0f, 1); 
sim.setNeuronParameters(MEC_LII_Basket_Speed, 20.0f, 0.0f,  1.0f, 0.0f, -55.0f, 0.0f, 
                                -40.0f, 0.0f, 0.15f, 0.0f, 8.0f, 0.0f, 25.0f, 0.0f, 
                                -55.0f, 0.0f, 200.0f, 0.0f, 1);
sim.setNeuronParameters(MEC_LII_Stellate_Speed, 118.000000f, 0.0f, 0.62f, 0.0f, -58.53f, 0.0f, -43.52f, 
                                0.0f, 0.005f, 0.0f, 11.690000f, 0.0f, 11.48f, 0.0f, -49.52f, 0.0f, 
                                50.0f, 0.0f, 1);
sim.setNeuronParameters(CA1_Pyramidal, 204.0f, 0.0f, 0.76f, 0.0f, -69.36f, 0.0f, -39.99f, 
                                0.0f, 0.001f, 0.0f, 0.01f, 0.0f, 25.46f, 0.0f, -54.95f, 
                                0.0f, 16.0f, 0.0f, 1);
/*sim.setNeuronParameters(CA1_Pyramidal, 204.0f, 0.0f, 0.37f, 0.0f, -70.53f, 0.0f, -39.99f, 
                                0.0f, 0.001f, 0.0f, 0.01f, 0.0f, 3.96f, 0.0f, -54.95f, 0.0f, 
                                7.0f, 0.0f, 1);*/

/* neuron connection parameters */
setInExcConns(&sim, &p);
double gc2inwt = p.gc_to_in_wt;
MexHatConnection* MexHatConn;
SomeToSomeConnection* SomeToSomeConn;    
sim.connect(EC_LI_II_Multipolar_Pyramidal, MEC_LII_Stellate, "one-to-one", p.dir_to_gc_wt, 1.0f, 
            RangeDelay(1), RadiusRF(-1), SYN_FIXED, 33.082, 20.0f); // 0 DIR
////
p.conn_offset = 0;
if (p.spin2in_active) {
    p.gc_to_in_wt = p.spdin2inwt;
    SomeToSomeConn = new SomeToSomeConnection(&p);
    sim.connect(MEC_LII_Basket_Speed, EC_LII_Axo_Axonic, SomeToSomeConn, 8.5, 5.2, SYN_FIXED);
}
if (p.spex2in_active) {
    p.gc_to_in_wt = p.spdex2inwt;
    SomeToSomeConn = new SomeToSomeConnection(&p);
    sim.connect(MEC_LII_Stellate_Speed, EC_LII_Axo_Axonic, SomeToSomeConn, 8.5, 5.2, SYN_FIXED);    
}
p.gc_to_in_wt = gc2inwt;
SomeToSomeConn = new SomeToSomeConnection(&p);
sim.connect(MEC_LII_Stellate, EC_LII_Axo_Axonic, SomeToSomeConn, 8.5, 5.2, SYN_FIXED);
MexHatConn = new MexHatConnection(&p);
sim.connect(EC_LII_Axo_Axonic, MEC_LII_Stellate, MexHatConn, 8.5, 5.2, SYN_FIXED); // 2 IN->GC one-to-many
////
p.conn_offset = 1;
if (p.spin2in_active) {
    p.gc_to_in_wt = p.spdin2inwt;
    SomeToSomeConn = new SomeToSomeConnection(&p);
    sim.connect(MEC_LII_Basket_Speed, MEC_LII_Basket, SomeToSomeConn, 8.5, 5.2, SYN_FIXED);
}
if (p.spex2in_active) {
    p.gc_to_in_wt = p.spdex2inwt;
    SomeToSomeConn = new SomeToSomeConnection(&p);
    sim.connect(MEC_LII_Stellate_Speed, MEC_LII_Basket, SomeToSomeConn, 8.5, 5.2, SYN_FIXED);
}
p.gc_to_in_wt = gc2inwt;
SomeToSomeConn = new SomeToSomeConnection(&p);
sim.connect(MEC_LII_Stellate, MEC_LII_Basket, SomeToSomeConn, 8.5, 5.2, SYN_FIXED);
MexHatConn = new MexHatConnection(&p);
sim.connect(MEC_LII_Basket, MEC_LII_Stellate, MexHatConn, 8.5, 5.2, SYN_FIXED); // 2 IN->GC one-to-many
////
p.conn_offset = 2;
if (p.spin2in_active) {
    p.gc_to_in_wt = p.spdin2inwt;
    SomeToSomeConn = new SomeToSomeConnection(&p);
    sim.connect(MEC_LII_Basket_Speed, EC_LII_Basket_Multipolar, SomeToSomeConn, 8.5, 5.2, SYN_FIXED);
}
if (p.spex2in_active) {
    p.gc_to_in_wt = p.spdex2inwt;
    SomeToSomeConn = new SomeToSomeConnection(&p);
    sim.connect(MEC_LII_Stellate_Speed, EC_LII_Basket_Multipolar, SomeToSomeConn, 8.5, 5.2, SYN_FIXED);
}
p.gc_to_in_wt = gc2inwt;
SomeToSomeConn = new SomeToSomeConnection(&p);
sim.connect(MEC_LII_Stellate, EC_LII_Basket_Multipolar, SomeToSomeConn, 8.5, 5.2, SYN_FIXED);
MexHatConn = new MexHatConnection(&p);
sim.connect(EC_LII_Basket_Multipolar, MEC_LII_Stellate, MexHatConn, 8.5, 5.2, SYN_FIXED); // 2 IN->GC one-to-many
sim.connect(CA1_Pyramidal, MEC_LII_Stellate, "one-to-one", p.pc_to_gc_wt, 1.0f, 
           RangeDelay(1), RadiusRF(-1), SYN_FIXED, 34.27, 21.0f); // 3 PCs
/*sim.connect(CA1_Pyramidal, MEC_LII_Stellate, "one-to-one", p.pc_to_gc_wt, 1.0f, 
            RangeDelay(1), RadiusRF(-1), SYN_FIXED, 33.082, 20.0f);*/

/* STP parameters */
// Keivan data conversion: g = conductance; t_d = STPtdAMPA or STPtdGABAa; u = U; t_f = tauU; t_r = tauX; 
#if ORIGINAL
sim.setSTP(EC_LI_II_Multipolar_Pyramidal, MEC_LII_Stellate, true, STPu(0.1513, 0.0f),
                                     STPtauU(69.11, 0.0f),
                                     STPtauX(98.1, 0.0f),
                                     STPtdAMPA(6.636, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, EC_LII_Axo_Axonic, true, STPu(0.1514, 0.0f), 
                                    STPtauU(58.97, 0.0f), 
                                    STPtauX(123.6932, 0.0f), 
                                    STPtdAMPA(3.0361104, 0.0f), 
                                    STPtdNMDA(150.0, 0.0f), 
                                    STPtdGABAa(6.0, 0.0f), 
                                    STPtdGABAb(150.0, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, MEC_LII_Basket, true, STPu(0.1638, 0.0f), 
                                    STPtauU(57.57, 0.0f), 
                                    STPtauX(118.9779, 0.0f), 
                                    STPtdAMPA(2.8213217, 0.0f), 
                                    STPtdNMDA(150.0, 0.0f), 
                                    STPtdGABAa(6.0, 0.0f), 
                                    STPtdGABAb(150.0, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true, STPu(0.1638, 0.0f), 
                                    STPtauU(57.57, 0.0f), 
                                    STPtauX(106.1875, 0.0f), 
                                    STPtdAMPA(2.5591583, 0.0f), 
                                    STPtdNMDA(150.0, 0.0f), 
                                    STPtdGABAa(6.0, 0.0f), 
                                    STPtdGABAb(150.0, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(EC_LII_Axo_Axonic, MEC_LII_Stellate, true, STPu(0.1100, 0.0f), 
                                    STPtauU(35.53, 0.0f), 
                                    STPtauX(385.3961, 0.0f), 
                                    STPtdAMPA(5.0f, 0.0f), 
                                    STPtdNMDA(150.0f, 0.0f), 
                                    STPtdGABAa(4.22285f, 0.0f), 
                                    STPtdGABAb(150.0f, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Basket, MEC_LII_Stellate, true, STPu(0.1119, 0.0f), 
                                    STPtauU(37.29, 0.0f), 
                                    STPtauX(401.7326, 0.0f), 
                                    STPtdAMPA(5.0f, 0.0f), 
                                    STPtdNMDA(150.0f, 0.0f), 
                                    STPtdGABAa(4.3151045f, 0.0f), 
                                    STPtdGABAb(150.0f, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(EC_LII_Basket_Multipolar, MEC_LII_Stellate, true, STPu(0.1119, 0.0f), 
                                    STPtauU(41.94, 0.0f), 
                                    STPtauX(374.8724, 0.0f), 
                                    STPtdAMPA(5.0f, 0.0f), 
                                    STPtdNMDA(150.0f, 0.0f), 
                                    STPtdGABAa(4.6974845f, 0.0f), 
                                    STPtdGABAb(150.0f, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(CA1_Pyramidal, MEC_LII_Stellate, true, STPu(0.1231, 0.0f),
                                     STPtauU(49.71, 0.0f),
                                     STPtauX(153.4, 0.0f),
                                     STPtdAMPA(6.674, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
#endif
// g,d,r,f,U
// g,d,x,u,U
// Facilitating: U:0.15 u:750.0 x:50.0 
// Depressing: U:0.45 u:50.0 x:750.0
#if FACILITATION
sim.setSTP(EC_LI_II_Multipolar_Pyramidal, MEC_LII_Stellate, true, STPu(0.15124615, 0.0f),
                                     STPtauU(69.11, 0.0f),
                                     STPtauX(98.07602, 0.0f),
                                     STPtdAMPA(3.4186974, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, EC_LII_Axo_Axonic, true, STPu(0.1514, 0.0f), 
                                    STPtauU(58.965103, 0.0f), 
                                    STPtauX(123.6932, 0.0f), 
                                    STPtdAMPA(3.0361104, 0.0f), 
                                    STPtdNMDA(150.0, 0.0f), 
                                    STPtdGABAa(6.0, 0.0f), 
                                    STPtdGABAb(150.0, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, MEC_LII_Basket, true, STPu(0.1638, 0.0f), 
                                    STPtauU(57.57, 0.0f), 
                                    STPtauX(118.9779, 0.0f), 
                                    STPtdAMPA(2.8213217, 0.0f), 
                                    STPtdNMDA(150.0, 0.0f), 
                                    STPtdGABAa(6.0, 0.0f), 
                                    STPtdGABAb(150.0, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true, STPu(0.18756935, 0.0f), 
                                    STPtauU(57.57, 0.0f), 
                                    STPtauX(106.1875, 0.0f), 
                                    STPtdAMPA(2.5591583, 0.0f), 
                                    STPtdNMDA(150.0, 0.0f), 
                                    STPtdGABAa(6.0, 0.0f), 
                                    STPtdGABAb(150.0, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(EC_LII_Axo_Axonic, MEC_LII_Stellate, true, STPu(0.1100, 0.0f), 
                                    STPtauU(35.53, 0.0f),
                                    STPtauX(355.84775, 0.0f),
                                    STPtdAMPA(5.0f, 0.0f),
                                    STPtdNMDA(150.0f, 0.0f),
                                    STPtdGABAa(4.22285f, 0.0f),
                                    STPtdGABAb(150.0f, 0.0f),
                                    STPtrNMDA(0.0f, 0.0f),
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Basket, MEC_LII_Stellate, true, STPu(0.1119, 0.0f), 
                                    STPtauU(37.29, 0.0f), 
                                    STPtauX(346.3008, 0.0f), 
                                    STPtdAMPA(5.0f, 0.0f), 
                                    STPtdNMDA(150.0f, 0.0f), 
                                    STPtdGABAa(4.3151045f, 0.0f), 
                                    STPtdGABAb(150.0f, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(EC_LII_Basket_Multipolar, MEC_LII_Stellate, true, STPu(0.13380751, 0.0f), 
                                    STPtauU(41.94, 0.0f), 
                                    STPtauX(311.77548, 0.0f), 
                                    STPtdAMPA(5.0f, 0.0f), 
                                    STPtdNMDA(150.0f, 0.0f), 
                                    STPtdGABAa(4.6974845f, 0.0f), 
                                    STPtdGABAb(150.0f, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(CA1_Pyramidal, MEC_LII_Stellate, true, STPu(0.1231, 0.0f),
                                     STPtauU(49.71, 0.0f),
                                     STPtauX(153.4, 0.0f),
                                     STPtdAMPA(6.674, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
#endif

#if DEPRESSION
sim.setSTP(EC_LI_II_Multipolar_Pyramidal, MEC_LII_Stellate, true, STPu(0.3051624, 0.0f),
                                     STPtauU(22.23344, 0.0f),
                                     STPtauX(583.25165, 0.0f),
                                     STPtdAMPA(3.4186974, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, EC_LII_Axo_Axonic, true, STPu(0.33274132, 0.0f), 
                                    STPtauU(20.05904, 0.0f), 
                                    STPtauX(738.60767, 0.0f), 
                                    STPtdAMPA(3.0361104, 0.0f), 
                                    STPtdNMDA(150.0, 0.0f), 
                                    STPtdGABAa(6.0, 0.0f), 
                                    STPtdGABAb(150.0, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, MEC_LII_Basket, true, STPu(0.32877067, 0.0f), 
                                    STPtauU(19.67583, 0.0f), 
                                    STPtauX(724.70306, 0.0f), 
                                    STPtdAMPA(2.8213217, 0.0f), 
                                    STPtdNMDA(150.0, 0.0f), 
                                    STPtdGABAa(6.0, 0.0f), 
                                    STPtdGABAb(150.0, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true, STPu(0.36625087, 0.0f), 
                                    STPtauU(24.876564, 0.0f), 
                                    STPtauX(738.1358, 0.0f), 
                                    STPtdAMPA(2.5591583, 0.0f), 
                                    STPtdNMDA(150.0, 0.0f), 
                                    STPtdGABAa(6.0, 0.0f), 
                                    STPtdGABAb(150.0, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(EC_LII_Axo_Axonic, MEC_LII_Stellate, true, STPu(0.2661683, 0.0f), 
                                    STPtauU(11.97847, 0.0f),
                                    STPtauX(1006.9757, 0.0f),
                                    STPtdAMPA(5.0f, 0.0f),
                                    STPtdNMDA(150.0f, 0.0f),
                                    STPtdGABAa(4.22285f, 0.0f),
                                    STPtdGABAb(150.0f, 0.0f),
                                    STPtrNMDA(0.0f, 0.0f),
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Basket, MEC_LII_Stellate, true, STPu(0.27121282, 0.0f), 
                                    STPtauU(12.000511, 0.0f), 
                                    STPtauX(983.24335, 0.0f), 
                                    STPtdAMPA(5.0f, 0.0f), 
                                    STPtdNMDA(150.0f, 0.0f), 
                                    STPtdGABAa(4.3151045f, 0.0f), 
                                    STPtdGABAb(150.0f, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(EC_LII_Basket_Multipolar, MEC_LII_Stellate, true, STPu(0.26842606, 0.0f), 
                                    STPtauU(13.102789, 0.0f), 
                                    STPtauX(827.2014, 0.0f), 
                                    STPtdAMPA(5.0f, 0.0f), 
                                    STPtdNMDA(150.0f, 0.0f), 
                                    STPtdGABAa(4.6974845f, 0.0f), 
                                    STPtdGABAb(150.0f, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(CA1_Pyramidal, MEC_LII_Stellate, true, STPu(0.1231, 0.0f),
                                     STPtauU(49.71, 0.0f),
                                     STPtauX(153.4, 0.0f),
                                     STPtdAMPA(6.674, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
#endif

#if BALANCE
sim.setSTP(EC_LI_II_Multipolar_Pyramidal, MEC_LII_Stellate, true, STPu(0.228, 0.0f),
                                     STPtauU(45.671, 0.0f),
                                     STPtauX(340.663835, 0.0f),
                                     STPtdAMPA(3.4186974, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, EC_LII_Axo_Axonic, true, STPu(0.242, 0.0f), 
                                    STPtauU(39.512, 0.0f), 
                                    STPtauX(431.150, 0.0f), 
                                    STPtdAMPA(3.0361104, 0.0f), 
                                    STPtdNMDA(150.0, 0.0f), 
                                    STPtdGABAa(6.0, 0.0f), 
                                    STPtdGABAb(150.0, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, MEC_LII_Basket, true, STPu(0.246, 0.0f), 
                                    STPtauU(38.623, 0.0f), 
                                    STPtauX(421.841, 0.0f), 
                                    STPtdAMPA(2.8213217, 0.0f), 
                                    STPtdNMDA(150.0, 0.0f), 
                                    STPtdGABAa(6.0, 0.0f), 
                                    STPtdGABAb(150.0, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true, STPu(0.277, 0.0f), 
                                    STPtauU(41.223, 0.0f), 
                                    STPtauX(422.161, 0.0f), 
                                    STPtdAMPA(2.5591583, 0.0f), 
                                    STPtdNMDA(150.0, 0.0f), 
                                    STPtdGABAa(6.0, 0.0f), 
                                    STPtdGABAb(150.0, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(EC_LII_Axo_Axonic, MEC_LII_Stellate, true, STPu(0.188, 0.0f), 
                                    STPtauU(23.754, 0.0f),
                                    STPtauX(681.412, 0.0f),
                                    STPtdAMPA(5.0f, 0.0f),
                                    STPtdNMDA(150.0f, 0.0f),
                                    STPtdGABAa(4.22285f, 0.0f),
                                    STPtdGABAb(150.0f, 0.0f),
                                    STPtrNMDA(0.0f, 0.0f),
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Basket, MEC_LII_Stellate, true, STPu(0.196, 0.0f), 
                                    STPtauU(24.645, 0.0f), 
                                    STPtauX(664.772, 0.0f), 
                                    STPtdAMPA(5.0f, 0.0f), 
                                    STPtdNMDA(150.0f, 0.0f), 
                                    STPtdGABAa(4.3151045f, 0.0f), 
                                    STPtdGABAb(150.0f, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(EC_LII_Basket_Multipolar, MEC_LII_Stellate, true, STPu(0.201, 0.0f), 
                                    STPtauU(27.521, 0.0f), 
                                    STPtauX(569.488, 0.0f), 
                                    STPtdAMPA(5.0f, 0.0f), 
                                    STPtdNMDA(150.0f, 0.0f), 
                                    STPtdGABAa(4.6974845f, 0.0f), 
                                    STPtdGABAb(150.0f, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(CA1_Pyramidal, MEC_LII_Stellate, true, STPu(0.1231, 0.0f),
                                     STPtauU(49.71, 0.0f),
                                     STPtauX(153.4, 0.0f),
                                     STPtdAMPA(6.674, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
#endif

#if BALANCE2
sim.setSTP(EC_LI_II_Multipolar_Pyramidal, MEC_LII_Stellate, true, STPu(0.1513, 0.0f),
                                     STPtauU(69.11, 0.0f),
                                     STPtauX(98.1, 0.0f),
                                     STPtdAMPA(3.4186974, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, EC_LII_Axo_Axonic, true, STPu(0.1514, 0.0f), 
                                    STPtauU(58.97, 0.0f), 
                                    STPtauX(123.6932, 0.0f), 
                                    STPtdAMPA(3.0361104, 0.0f), 
                                    STPtdNMDA(150.0, 0.0f), 
                                    STPtdGABAa(6.0, 0.0f), 
                                    STPtdGABAb(150.0, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, MEC_LII_Basket, true, STPu(0.1638, 0.0f), 
                                    STPtauU(57.57, 0.0f), 
                                    STPtauX(118.9779, 0.0f), 
                                    STPtdAMPA(2.8213217, 0.0f), 
                                    STPtdNMDA(150.0, 0.0f), 
                                    STPtdGABAa(6.0, 0.0f), 
                                    STPtdGABAb(150.0, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true, STPu(0.18756935, 0.0f), 
                                    STPtauU(57.57, 0.0f), 
                                    STPtauX(106.1875, 0.0f), 
                                    STPtdAMPA(2.5591583, 0.0f), 
                                    STPtdNMDA(150.0, 0.0f), 
                                    STPtdGABAa(6.0, 0.0f), 
                                    STPtdGABAb(150.0, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(EC_LII_Axo_Axonic, MEC_LII_Stellate, true, STPu(0.1100, 0.0f), 
                                    STPtauU(35.53, 0.0f), 
                                    STPtauX(385.3961, 0.0f), 
                                    STPtdAMPA(5.0f, 0.0f), 
                                    STPtdNMDA(150.0f, 0.0f), 
                                    STPtdGABAa(4.22285f, 0.0f), 
                                    STPtdGABAb(150.0f, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Basket, MEC_LII_Stellate, true, STPu(0.1119, 0.0f), 
                                    STPtauU(37.29, 0.0f), 
                                    STPtauX(401.7326, 0.0f), 
                                    STPtdAMPA(5.0f, 0.0f), 
                                    STPtdNMDA(150.0f, 0.0f), 
                                    STPtdGABAa(4.3151045f, 0.0f), 
                                    STPtdGABAb(150.0f, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(EC_LII_Basket_Multipolar, MEC_LII_Stellate, true, STPu(0.13380751, 0.0f), 
                                    STPtauU(41.94, 0.0f), 
                                    STPtauX(374.8724, 0.0f), 
                                    STPtdAMPA(5.0f, 0.0f), 
                                    STPtdNMDA(150.0f, 0.0f), 
                                    STPtdGABAa(4.6974845f, 0.0f), 
                                    STPtdGABAb(150.0f, 0.0f), 
                                    STPtrNMDA(0.0f, 0.0f), 
                                    STPtrGABAb(0.0f, 0.0f));
sim.setSTP(CA1_Pyramidal, MEC_LII_Stellate, true, STPu(0.1231, 0.0f),
                                     STPtauU(49.71, 0.0f),
                                     STPtauX(153.4, 0.0f),
                                     STPtdAMPA(6.674, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
/*sim.setSTP(CA1_Pyramidal, MEC_LII_Stellate, true, STPu(0.1513, 0.0f),
                                     STPtauU(69.11, 0.0f),
                                     STPtauX(98.1, 0.0f),
                                     STPtdAMPA(3.4186974, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));*/
#endif

/* neuron monitors */
#if monitor_voltage
    sim.setNeuronMonitor(MEC_LII_Stellate,"DEFAULT");
    sim.setNeuronMonitor(MEC_LII_Basket,"DEFAULT");
    sim.setNeuronMonitor(CA1_Pyramidal,"DEFAULT");
    sim.setNeuronMonitor(MEC_LII_Basket_Speed,"DEFAULT");
#endif