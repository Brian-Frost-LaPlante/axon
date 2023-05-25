function netSim(;λs = 0.1:0.01:0.4, celltypes = [0,-1,1],
    NUM_REALIZATIONS = 1000, NUM_TIMESTEPS = 1000, coherent = true, damaged = false, fb = false,
    earlystop = false)

    NUM_SPIKES = zeros(length(λs))
    ISI = zeros(length(λs))

    spike(λ) = Int(rand() < λ)

    # just doing the simple EE control network

    for λᵢ = 1:length(λs)

        for NN = 1:NUM_REALIZATIONS

            t_last = 0 # for computing ISI
            n1 = neuron()
            n1.type = celltypes[1]
            n2 = neuron()
            n2.type = celltypes[2]
            n3 = neuron()
            n3.type = celltypes[3]
            
            for TT = 1:NUM_TIMESTEPS
            
                # generate spike and read outputs
                in1 = spike(λs[λᵢ])
                if damaged &&  (abs(n2.out) > .5)
                    n2.out = n2.type*guessOut(n2.train)
                    n2.train[9] = guessOut(n2.train)
                end

                if coherent
                
                    if fb
                        in2 = n1.out + n3.out + in1
                    else
                        in2 = n1.out + in1
                    end

                    in3 = n2.out + in1
                
                else
                
                    if fb
                        in2 = n1.out + n3.out + spike(λs[λᵢ])
                    else
                        in2 = n1.out + spike(λs[λᵢ])
                    end

                    in3 = n2.out + spike(λs[λᵢ])
                
                end

                neuronUpdate(n1,in1)
                neuronUpdate(n2,in2)
                neuronUpdate(n3,in3)

                NUM_SPIKES[λᵢ] = NUM_SPIKES[λᵢ] + abs(n3.out)
                if abs(n3.out) > 0.5
                    ISI[λᵢ] = ISI[λᵢ] + (TT - t_last)/10 # dt = .1 ms so /10 to get in ms
                    t_last = TT
                end
            end
        end
        if earlystop && (ISI[λᵢ]/NUM_SPIKES[λᵢ] < 1.1)
            println(λs[λᵢ]*1e4)
            return λs[λᵢ]*1e4, λs[λᵢ]*1e4
        end
    end

    ISI = ISI./NUM_SPIKES
    
    ii = 1
    while (ISI[ii] > 1.1) && (ii < length(λs))
        ii = ii + 1
    end
    println(λs[ii]*1e4)

    NUM_SPIKES = NUM_SPIKES/NUM_REALIZATIONS

    
    println("Job's done!")
    
    return(NUM_SPIKES, ISI)

end
