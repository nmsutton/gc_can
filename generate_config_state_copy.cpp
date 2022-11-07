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
//int MEC_LII_Basket_Speed2=sim.createGroup("MEC_LII_Basket_Speed2", 
//                            p.MEC_LII_Basket_Speed2_Count, INHIBITORY_NEURON, ANY, GPU_CORES);
int MEC_LII_Basket_Speed3=sim.createGroup("MEC_LII_Basket_Speed3", 
                            p.MEC_LII_Basket_Speed2_Count, INHIBITORY_NEURON, ANY, GPU_CORES);
int MEC_LII_Basket_Speed4=sim.createGroup("MEC_LII_Basket_Speed4", 
                            p.MEC_LII_Basket_Speed2_Count, INHIBITORY_NEURON, ANY, GPU_CORES);
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
//p.MEC_LII_Basket_Speed2_Group = MEC_LII_Basket_Speed2; // 7
p.MEC_LII_Stellate_Speed_Group = MEC_LII_Stellate_Speed; // 8
p.MEC_LII_Basket_Speed3_Group = MEC_LII_Basket_Speed3; // 9
p.MEC_LII_Basket_Speed4_Group = MEC_LII_Basket_Speed4; // 10

/* neuron type parameters */
sim.setNeuronParameters(EC_LI_II_Multipolar_Pyramidal, 204.0f, 0.0f, 0.37f, 0.0f, -70.53f, 0.0f, -39.99f, 
                                0.0f, 0.001f, 0.0f, 0.01f, 0.0f, 3.96f, 0.0f, -54.95f, 0.0f, 
                                7.0f, 0.0f, 1); // C,k,vr,vt,a,b,vpeak,c,d
                                // Ensemble file:  k,a,b,d,C,vr,vt,c,vpeak. 
                                // 1->2, 2->5, 3->6, 4->9, 5->1, 6->3, 7->4, 8->8, 9->7
//sim.setNeuronParameters(MEC_LII_Stellate, 118.000000f, 0.0f, 0.62f, 0.0f, -58.53f, 0.0f, -43.52f, 0.0f, 0.003f, 0.0f, 11.690000f, 0.0f, 11.48f, 0.0f, -49.52f, 0.0f, 50.0f, 0.0f, 1);
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
//sim.setNeuronParameters(MEC_LII_Basket_Speed2, 20.0f, 0.0f,  1.0f, 0.0f, -55.0f, 0.0f, 
//                                -40.0f, 0.0f, 0.15f, 0.0f, 8.0f, 0.0f, 25.0f, 0.0f, 
//                                -55.0f, 0.0f, 200.0f, 0.0f, 1); 
sim.setNeuronParameters(MEC_LII_Basket_Speed3, 20.0f, 0.0f,  1.0f, 0.0f, -55.0f, 0.0f, 
                                -40.0f, 0.0f, 0.15f, 0.0f, 8.0f, 0.0f, 25.0f, 0.0f, 
                                -55.0f, 0.0f, 200.0f, 0.0f, 1); 
sim.setNeuronParameters(MEC_LII_Basket_Speed4, 20.0f, 0.0f,  1.0f, 0.0f, -55.0f, 0.0f, 
                                -40.0f, 0.0f, 0.15f, 0.0f, 8.0f, 0.0f, 25.0f, 0.0f, 
                                -55.0f, 0.0f, 200.0f, 0.0f, 1);
/*sim.setNeuronParameters(MEC_LII_Stellate_Speed, 118.000000f, 0.0f, 0.62f, 0.0f, -58.53f, 0.0f, -43.52f, 
                                0.0f, 0.005f, 0.0f, 11.690000f, 0.0f, 11.48f, 0.0f, -49.52f, 0.0f, 
                                50.0f, 0.0f, 1);*/
sim.setNeuronParameters(MEC_LII_Stellate_Speed, 118.000000f, 0.0f, 0.62f, 0.0f, -58.53f, 0.0f, -43.52f, 
                                0.0f, 0.005f, 0.0f, 11.690000f, 0.0f, 11.48f, 0.0f, -49.52f, 0.0f, 
                                50.0f, 0.0f, 1);
sim.setNeuronParameters(CA1_Pyramidal, 204.0f, 0.0f, 0.76f, 0.0f, -69.36f, 0.0f, -39.99f, 
                                0.0f, 0.001f, 0.0f, 0.01f, 0.0f, 25.46f, 0.0f, -54.95f, 
                                0.0f, 16.0f, 0.0f, 1);

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
    sim.connect(MEC_LII_Basket_Speed3, EC_LII_Axo_Axonic, SomeToSomeConn, 8.5, 5.2, SYN_FIXED);
    sim.connect(MEC_LII_Basket_Speed4, EC_LII_Axo_Axonic, SomeToSomeConn, 8.5, 5.2, SYN_FIXED);
}
/*if (p.spin2ex_active) {
    p.gc_to_in_wt = p.spdin2exwt;
    SomeToSomeConn = new SomeToSomeConnection(&p);
    sim.connect(MEC_LII_Basket_Speed2, MEC_LII_Stellate, "one-to-one", p.spdin2exwt, 1.0f, 
            RangeDelay(1), RadiusRF(-1), SYN_FIXED, 9.654, 5.92f); // 0 DIR
}*/
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
    sim.connect(MEC_LII_Basket_Speed3, MEC_LII_Basket, SomeToSomeConn, 8.5, 5.2, SYN_FIXED);
    sim.connect(MEC_LII_Basket_Speed4, MEC_LII_Basket, SomeToSomeConn, 8.5, 5.2, SYN_FIXED);
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
    sim.connect(MEC_LII_Basket_Speed3, EC_LII_Basket_Multipolar, SomeToSomeConn, 8.5, 5.2, SYN_FIXED);
    sim.connect(MEC_LII_Basket_Speed4, EC_LII_Basket_Multipolar, SomeToSomeConn, 8.5, 5.2, SYN_FIXED);
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

/* STP parameters */
// Keivan data conversion: g = conductance; t_d = STPtdAMPA or STPtdGABAa; u = U; t_f = tauU; t_r = tauX; 
sim.setSTP(EC_LI_II_Multipolar_Pyramidal, MEC_LII_Stellate, true, STPu(0.1513, 0.0f),
                                     STPtauU(69.11, 0.0f),
                                     STPtauX(98.1, 0.0f),
                                     STPtdAMPA(6.636, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, EC_LII_Axo_Axonic, true, STPu(0.1514, 0.0f), STPtauU(58.97, 0.0f), STPtauX(123.6932, 0.0f), STPtdAMPA(3.0361104, 0.0f), STPtdNMDA(150.0, 0.0f), STPtdGABAa(6.0, 0.0f), STPtdGABAb(150.0, 0.0f), STPtrNMDA(0.0f, 0.0f), STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, MEC_LII_Basket, true, STPu(0.1638, 0.0f), STPtauU(57.57, 0.0f), STPtauX(118.9779, 0.0f), STPtdAMPA(2.8213217, 0.0f), STPtdNMDA(150.0, 0.0f), STPtdGABAa(6.0, 0.0f), STPtdGABAb(150.0, 0.0f), STPtrNMDA(0.0f, 0.0f), STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate, EC_LII_Basket_Multipolar, true, STPu(0.1638, 0.0f), STPtauU(57.57, 0.0f), STPtauX(106.1875, 0.0f), STPtdAMPA(2.5591583, 0.0f), STPtdNMDA(150.0, 0.0f), STPtdGABAa(6.0, 0.0f), STPtdGABAb(150.0, 0.0f), STPtrNMDA(0.0f, 0.0f), STPtrGABAb(0.0f, 0.0f));

if (p.spin2in_active) {
sim.setSTP(MEC_LII_Basket_Speed, EC_LII_Axo_Axonic, true, STPu(0.1638, 0.0f),
                                     STPtauU(57.57, 0.0f),
                                     STPtauX(119, 0.0f),
                                     STPtdAMPA(6.205, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Basket_Speed, MEC_LII_Basket, true, STPu(0.1638, 0.0f),
                                     STPtauU(57.57, 0.0f),
                                     STPtauX(119, 0.0f),
                                     STPtdAMPA(6.205, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Basket_Speed, EC_LII_Basket_Multipolar, true, STPu(0.1638, 0.0f),
                                     STPtauU(57.57, 0.0f),
                                     STPtauX(119, 0.0f),
                                     STPtdAMPA(6.205, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Basket_Speed3, EC_LII_Axo_Axonic, true, STPu(0.1638, 0.0f),
                                     STPtauU(57.57, 0.0f),
                                     STPtauX(119, 0.0f),
                                     STPtdAMPA(6.205, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Basket_Speed3, MEC_LII_Basket, true, STPu(0.1638, 0.0f),
                                     STPtauU(57.57, 0.0f),
                                     STPtauX(119, 0.0f),
                                     STPtdAMPA(6.205, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Basket_Speed3, EC_LII_Basket_Multipolar, true, STPu(0.1638, 0.0f),
                                     STPtauU(57.57, 0.0f),
                                     STPtauX(119, 0.0f),
                                     STPtdAMPA(6.205, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Basket_Speed4, EC_LII_Axo_Axonic, true, STPu(0.1638, 0.0f),
                                     STPtauU(57.57, 0.0f),
                                     STPtauX(119, 0.0f),
                                     STPtdAMPA(6.205, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Basket_Speed4, MEC_LII_Basket, true, STPu(0.1638, 0.0f),
                                     STPtauU(57.57, 0.0f),
                                     STPtauX(119, 0.0f),
                                     STPtdAMPA(6.205, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Basket_Speed4, EC_LII_Basket_Multipolar, true, STPu(0.1638, 0.0f),
                                     STPtauU(57.57, 0.0f),
                                     STPtauX(119, 0.0f),
                                     STPtdAMPA(6.205, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
}
/*if (p.spin2ex_active) {
sim.setSTP(MEC_LII_Basket_Speed2, MEC_LII_Stellate, true, STPu(0.1638, 0.0f),
                                     STPtauU(57.57, 0.0f),
                                     STPtauX(119, 0.0f),
                                     STPtdAMPA(6.205, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
}*/
if (p.spex2in_active) {
sim.setSTP(MEC_LII_Stellate_Speed, EC_LII_Axo_Axonic, true, STPu(0.1514, 0.0f),
                                     STPtauU(58.97, 0.0f),
                                     STPtauX(123.7, 0.0f),
                                     STPtdAMPA(6.632, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate_Speed, MEC_LII_Basket, true, STPu(0.1638, 0.0f),
                                     STPtauU(57.57, 0.0f),
                                     STPtauX(119, 0.0f),
                                     STPtdAMPA(6.205, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Stellate_Speed, EC_LII_Basket_Multipolar, true, STPu(0.1638, 0.0f),
                                     STPtauU(57.57, 0.0f),
                                     STPtauX(119, 0.0f),
                                     STPtdAMPA(6.205, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));
}
sim.setSTP(EC_LII_Axo_Axonic, MEC_LII_Stellate, true, STPu(0.1100, 0.0f), STPtauU(35.53, 0.0f), STPtauX(385.3961, 0.0f), STPtdAMPA(5.0f, 0.0f), STPtdNMDA(150.0f, 0.0f), STPtdGABAa(4.22285f, 0.0f), STPtdGABAb(150.0f, 0.0f), STPtrNMDA(0.0f, 0.0f), STPtrGABAb(0.0f, 0.0f));
sim.setSTP(MEC_LII_Basket, MEC_LII_Stellate, true, STPu(0.1119, 0.0f), STPtauU(37.29, 0.0f), STPtauX(401.7326, 0.0f), STPtdAMPA(5.0f, 0.0f), STPtdNMDA(150.0f, 0.0f), STPtdGABAa(4.3151045f, 0.0f), STPtdGABAb(150.0f, 0.0f), STPtrNMDA(0.0f, 0.0f), STPtrGABAb(0.0f, 0.0f));
sim.setSTP(EC_LII_Basket_Multipolar, MEC_LII_Stellate, true, STPu(0.1119, 0.0f), STPtauU(41.94, 0.0f), STPtauX(374.8724, 0.0f), STPtdAMPA(5.0f, 0.0f), STPtdNMDA(150.0f, 0.0f), STPtdGABAa(4.6974845f, 0.0f), STPtdGABAb(150.0f, 0.0f), STPtrNMDA(0.0f, 0.0f), STPtrGABAb(0.0f, 0.0f));

sim.setSTP(CA1_Pyramidal, MEC_LII_Stellate, true, STPu(0.1231, 0.0f),
                                     STPtauU(49.71, 0.0f),
                                     STPtauX(153.4, 0.0f),
                                     STPtdAMPA(6.674, 0.0f),
                                     STPtdNMDA(150.0, 0.0f),
                                     STPtdGABAa(6.0, 0.0f),
                                     STPtdGABAb(150.0, 0.0f),
                                     STPtrNMDA(0.0f, 0.0f),
                                     STPtrGABAb(0.0f, 0.0f));

/* neuron monitors */
#if monitor_voltage
    sim.setNeuronMonitor(MEC_LII_Stellate,"DEFAULT");
    sim.setNeuronMonitor(MEC_LII_Basket,"DEFAULT");
    sim.setNeuronMonitor(CA1_Pyramidal,"DEFAULT");
    sim.setNeuronMonitor(MEC_LII_Basket_Speed,"DEFAULT");
#endif